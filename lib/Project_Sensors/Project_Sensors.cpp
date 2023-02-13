/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_BME280.h>
#include <TimeLib.h>
#include <Project_OLED.h>
#include <Project_Sensors.h>

static Adafruit_ADS1115 ads;
static Adafruit_BME280 bme;

/**
 * Constructor
 */
Sensors::Sensors(void) {}

/**
 * Sensor initialization.
 * sensors: ADS1115, BME280, MQ135,
 */
void Sensors::initSensors(Oled *_disp)
{
  _disp->showInitSensors();

  // Initialization ADS module
  ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V 1bit = 3mV 0.1875mV (default)
  if (!ads.begin(ADDR_ADS, &Wire))
    _disp->showInitSensors(12, true);
  else
    _disp->showInitSensors(12, false);

  // Initialization BME module
  if (!bme.begin(ADDR_BME, &Wire))
    _disp->showInitSensors(22, true);
  else
    _disp->showInitSensors(22, false);
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF);

  // Initialization MQ module
  pinMode(PIN_MQ_OUT, OUTPUT);
  digitalWrite(PIN_MQ_OUT, HIGH);
  delay(10);
  pinMode(PIN_MQ_IN, INPUT);
  if (!digitalRead(PIN_MQ_IN))
    _disp->showInitSensors(52, true);
  else
    _disp->showInitSensors(52, false);
  delay(2000);
  digitalWrite(PIN_MQ_OUT, LOW); // ????
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
  // Time & Date DATA
  mas[0] = day();
  mas[1] = month();
  mas[2] = year();
  mas[3] = hour();
  mas[4] = minute();

  // ADS SENSOR
  int16_t _adc;
  for (int8_t i = 0; i < 4; i++)
  {
    _adc = ads.readADC_SingleEnded(i) * MultFactor[i];
    mas[(i * 2 + 5)] = getFipVolts(_adc);
    mas[(i * 2 + 6)] = getSipVolts(_adc);
  }

  // BME SENSOR
  // Only needed in forced mode! In normal mode, you can remove the next line.
  bme.takeForcedMeasurement(); // has no effect in normal mode
  mas[13] = bme.readTemperature();
  mas[14] = bme.readPressure() / 100.0F;
  mas[15] = bme.readHumidity();

  // MQ SENSOR
  mas[16] = mas[11] + mas[12]; // расчет качества воздуха в %
}

/**
 * Get date
 */
String Sensors::getDate(void) { return (String)day() + '.' + (String)month() + '.' + (String)year(); }

/**
 * Get time
 */
String Sensors::getTime(void) { return (String)hour() + ':' + (String)minute(); }

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