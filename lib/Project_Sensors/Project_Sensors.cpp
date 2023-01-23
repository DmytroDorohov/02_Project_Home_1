/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_BME280.h>
#include <Project_Sensors.h>
#include <Project_OLED.h>

// const int ADDR_ADS = 0x10;              // ADS1115 address on I2C
const int ADDR_BME = 0x77; // BME280 address on I2C (0x77h or 0x76h)

Adafruit_ADS1115 ads;
Adafruit_BME280 bme;

void initSensors()
{
  int count = 0;
  showInitSensors(0);
  // Initialization ADS module
  ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V 1bit = 3mV 0.1875mV (default)
  if (!ads.begin())
    showInitSensors(10) else
    {
      showInitWifi(11);
      count++;
    };

  // Initialization BME module
  if (!bme.begin())
    showInitSensors(20) else
    {
      showInitWifi(21);
      count++;
    };

  // Initialization MQ module
  pinMode(S2, OUTPUT);
  pinMode(S3, INPUT);
  digitalWrite(S2, HIGH);
  if (!digitalRead(S3))
    showInitSensors(30) else showInitSensors(31);
  count++;

  // Initialization result
  if (count == 3)
    showInitSensors(55);
}

// data array formation
void getData(int16_t *mas)
{
  for (int i = 0; i < 10; i++)
  {
    mas[i] = i;
  }
  // some code
}