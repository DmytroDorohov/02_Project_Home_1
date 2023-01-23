/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_BME280.h>
#include <Project_Sensors.h>
#include <Project_OLED.h>

// const int ADDR_ADS = 0x48;              // ADS1115 address on I2C
const int ADDR_BME = 0x76; // BME280 address on I2C (0x77h or 0x76h)

Adafruit_ADS1115 ads;
Adafruit_BME280 bme;

void initSensors()
{
  int count = 0;
  showInitSensors(0);
  // Initialization ADS module
  ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V 1bit = 3mV 0.1875mV (default)
  if (!ads.begin())
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
}

// data array formation
void getData(int16_t *mas)
{
  // ADS SENSOR
  // float volts0
  // volts0 = ads.computeVolts(adc0);
  mas[2] = ads.readADC_SingleEnded(0);
  mas[3] = ads.readADC_SingleEnded(1);
  mas[4] = ads.readADC_SingleEnded(2);
  mas[5] = ads.readADC_SingleEnded(3);
  // BME SENSOR
  // Only needed in forced mode! In normal mode, you can remove the next line.
  bme.takeForcedMeasurement(); // has no effect in normal mode
  mas[6] = bme.readTemperature();
  mas[7] = bme.readPressure() / 100.0F;
  mas[8] = bme.readHumidity();
}