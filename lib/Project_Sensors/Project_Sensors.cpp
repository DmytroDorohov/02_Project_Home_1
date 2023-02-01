/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_BME280.h>
#include <RTClib.h>
#include <Project_Sensors.h>
#include <Project_OLED.h>

Adafruit_ADS1115 ads;
Adafruit_BME280 bme;
RTC_DS1307 rtc;
Oled _disp;

/**
 * Constructor
 */
Sensors::Sensors(int8_t ads, int8_t bme, int8_t ds, int8_t at, int8_t pmi, int8_t pmo)
{
  _addr_ads = ads;
  _addr_bme = bme;
  _addr_ds = ds;
  _addr_at = at;
  _pin_mq_in = pmi;
  _pin_mq_out = pmo;
}

/**
 * Sensor initialization.
 * sensors: ADS1115, BME280, MQ135, DS1307, AT24
 */
void Sensors::initSensors(void)
{
  _disp.showInitSensors();

  // Initialization ADS module
  ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V 1bit = 3mV 0.1875mV (default)
  if (!ads.begin(_addr_ads, &Wire))
    _disp.showInitSensors(10, true);
  else
    _disp.showInitSensors(10, false);

  // Initialization BME module
  if (!bme.begin(_addr_bme, &Wire))
    _disp.showInitSensors(20, true);
  else
    _disp.showInitSensors(20, false);
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF);

  // Initialization RTC module
  if (!rtc.begin())
    _disp.showInitSensors(30, true);
  else
    _disp.showInitSensors(30, false);

  // Initialization AT module
  _disp.showInitSensors(40, false);

  // Initialization MQ module
  pinMode(_pin_mq_out, OUTPUT);
  pinMode(_pin_mq_in, INPUT);
  digitalWrite(_pin_mq_out, HIGH);
  if (!digitalRead(_pin_mq_in))
    _disp.showInitSensors(50, true);
  else
    _disp.showInitSensors(50, false);
}

/**
 * Data array formation.
 * data array structure:
 * 18 elements
 * | day | month | year | hour | minute | Ua0 | Ua0 | Ua1 | Ua1 | Ua2 | Ua2 | Ua3 | Ua3 | temperature | pressure | humidity | quality | errors |
 * |  0  |   1   |   2  |   3  |    4   |  5  |  6  |  7  |  8  |  9  |  10 |  11 |  12 |      13     |    14    |    15    |    16   |   17   |
 */
void Sensors::getData(int16_t *mas)
{
  // ADS SENSOR
  int16_t _adc;
  for (int8_t i = 0; i < 4; i++)
  {
    _adc = ads.readADC_SingleEnded(i);
    mas[(i * 2 + 5)] = getFipVolts(_adc);
    mas[(i * 2 + 6)] = getSipVolts(_adc);
  }

  // BME SENSOR
  // Only needed in forced mode! In normal mode, you can remove the next line.
  bme.takeForcedMeasurement(); // has no effect in normal mode
  mas[13] = bme.readTemperature();
  mas[14] = bme.readPressure() / 100.0F;
  mas[15] = bme.readHumidity();
}

/**
 * Getting the first integer part of the measured voltage
 */
int16_t Sensors::getFipVolts(int16_t volt)
{
  float _volt;
  _volt = ads.computeVolts(volt); // voltage calculation
  return (int16_t)_volt;
}

/**
 * Getting the second integer part of the measured voltage
 */
int16_t Sensors::getSipVolts(int16_t volt)
{
  float _volt;
  _volt = ads.computeVolts(volt); // voltage calculation
  _volt -= (int16_t)_volt;
  return (int16_t)(_volt * 100);
}