/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_BME280.h>
#include <Project_Sensors.h>
#include <Project_OLED.h>

const int ADDR_ADS = 0x48; // ADS1115 address on I2C
const int ADDR_BME = 0x76; // BME280 address on I2C (0x77h or 0x76h)
const int ADDR_DS = 0x68;  // DS1307 address on I2C
// 0x50 at24

Adafruit_ADS1115 ads;
Adafruit_BME280 bme;

//**********************************************************************************************************************************************
// Sensor initialization.
// sensors: ADS1115, BME280, MQ135, DS1307
//**********************************************************************************************************************************************
void initSensors()
{
  int count = 0;
  showInitSensors(0);

  // Initialization ADS module
  ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V 1bit = 3mV 0.1875mV (default)
  if (!ads.begin(ADDR_ADS, &Wire))
    showInitSensors(10);
  else
  {
    showInitSensors(11);
    count++;
  };

  // Initialization BME module
  if (!bme.begin(ADDR_BME, &Wire))
    showInitSensors(20);
  else
  {
    showInitSensors(21);
    count++;
  };
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF);

  // Initialization MQ module
  pinMode(D7, OUTPUT);
  pinMode(D8, INPUT);
  digitalWrite(D7, HIGH);
  if (!digitalRead(D8))
    showInitSensors(30);
  else
    showInitSensors(31);
  count++;

  // Initialization DS module
  // some code
}

//**********************************************************************************************************************************************
// Data array formation.
// data array structure:
// 18 elements
// | day | month | year | hour | minute | Ua0 | Ua0 | Ua1 | Ua1 | Ua2 | Ua2 | Ua3 | Ua3 | temperature | pressure | humidity | quality | errors |
// |  0  |   1   |   2  |   3  |    4   |  5  |  6  |  7  |  8  |  9  |  10 |  11 |  12 |      13     |    14    |    15    |    16   |   17   |
//**********************************************************************************************************************************************
void getData(int16_t *mas)
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

//**********************************************************************************************************************************************
// Getting the first integer part of the measured voltage
//**********************************************************************************************************************************************
int16_t getFipVolts(int16_t volt)
{
  float _volt;
  _volt = ads.computeVolts(volt); // voltage calculation
  return (int16_t)_volt;
}

//**********************************************************************************************************************************************
// Getting the second integer part of the measured voltage
//**********************************************************************************************************************************************
int16_t getSipVolts(int16_t volt)
{
  float _volt;
  _volt = ads.computeVolts(volt); // voltage calculation
  _volt -= (int16_t)_volt;
  return (int16_t)(_volt * 100);
}