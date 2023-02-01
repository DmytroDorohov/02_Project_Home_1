/*
Описание библиотеки
*/

#ifndef Project_Sensors_h
#define Project_Sensors_h
#include <Arduino.h>

class Sensors
{
public:
  Sensors(int8_t, int8_t, int8_t, int8_t, int8_t, int8_t); // constructor
  void initSensors(void);                                  // initialization sensors
  void getData(int16_t *);                                 // get data in massiv from sensors
private:
  // functions
  int16_t getFipVolts(int16_t); // getting the first integer part of the measured voltage
  int16_t getSipVolts(int16_t); // getting the second integer part of the measured voltage
  // data
  int8_t _addr_ads, _addr_bme, _addr_ds, _addr_at, _pin_mq_in, _pin_mq_out;
};

#endif