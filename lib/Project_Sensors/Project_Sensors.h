/*
Описание библиотеки
*/

#ifndef Project_Sensors_h
#define Project_Sensors_h
#include <Arduino.h>

#define ADDR_ADS 0x48 // ADS1115 address on I2C
#define ADDR_BME 0x76 // BME280 address on I2C (0x77h or 0x76h)
#define PIN_MQ_IN D6  // MQ135 input pin
#define PIN_MQ_OUT D5 // MQ135 output pin

const float MultFactor[] = {1, 8.19, 8.268, 1}; // multiplication factor voltage on A0-A3 input

class Sensors
{
public:
  Sensors(void);            // constructor
  void initSensors(Oled *); // initialization sensors
  void getData(int16_t *);  // get data in massiv from sensors
  String getDate(void);     // get date
  String getTime(void);     // get time
private:
  int16_t getFipVolts(int16_t); // getting the first integer part of the measured voltage
  int16_t getSipVolts(int16_t); // getting the second integer part of the measured voltage
};

#endif