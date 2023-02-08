/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_BME280.h>
#include <RTClib.h>
#include <Project_OLED.h>
#include <Project_Sensors.h>

static Adafruit_ADS1115 ads;
static Adafruit_BME280 bme;
static RTC_DS1307 rtc;

/**
 * Constructor
 */
Sensors::Sensors(void) {}

/**
 * Sensor initialization.
 * sensors: ADS1115, BME280, MQ135, DS1307, AT24
 */
void Sensors::initSensors(int8_t _addr_ads, int8_t _addr_bme, int8_t _addr_ds, int8_t _addr_at, int8_t _pin_mq_in, int8_t _pin_mq_out, Oled *_disp)
{
  _disp->showInitSensors();

  // Initialization ADS module
  ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V 1bit = 3mV 0.1875mV (default)
  if (!ads.begin(_addr_ads, &Wire))
    _disp->showInitSensors(12, true);
  else
    _disp->showInitSensors(12, false);

  // Initialization BME module
  if (!bme.begin(_addr_bme, &Wire))
    _disp->showInitSensors(22, true);
  else
    _disp->showInitSensors(22, false);
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF);

  // Initialization RTC module
  if (!rtc.begin())
    _disp->showInitSensors(32, true);
  else
    _disp->showInitSensors(32, false);
  if (!rtc.isrunning())
  {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // Initialization AT module
  _disp->showInitSensors(42, false);

  // Initialization MQ module
  pinMode(_pin_mq_out, OUTPUT);
  pinMode(_pin_mq_in, INPUT);
  digitalWrite(_pin_mq_out, HIGH);
  delay(10);
  if (!digitalRead(_pin_mq_in))
    _disp->showInitSensors(52, true);
  else
    _disp->showInitSensors(52, false);
  digitalWrite(_pin_mq_out, LOW); // ????
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
  // RTC DATA
  DateTime time = rtc.now();
  mas[0] = time.day();
  mas[1] = time.month();
  mas[2] = time.year();
  mas[3] = time.hour();
  mas[4] = time.minute();

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

  // MQ SENSOR
  mas[16] = mas[11] + mas[12]; // расчет качества воздуха в %
}

/**
 * Get RTC date
 */
String Sensors::getDate(void)
{
  char buf[] = "DD.MM.YYYY";
  DateTime time = rtc.now();
  return time.toString(buf);
}

/**
 * Get RTC time
 */
String Sensors::getTime(void)
{
  char buf[] = "hh:mm";
  DateTime time = rtc.now();
  return time.toString(buf);
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