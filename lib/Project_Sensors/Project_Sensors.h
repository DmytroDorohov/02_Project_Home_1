/*
Описание библиотеки
*/

#ifndef Project_Sensors_h
#define Project_Sensors_h
#include <Arduino.h>

class Sensors
{
public:
  Sensors(void);                                                            // constructor
  void initSensors(int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, Oled *); // initialization sensors
  void getData(int16_t *);                                                  // get data in massiv from sensors
  String getDate(void);                                                     // get RTC date
  String getTime(void);                                                     // get RTC time
private:
  // functions
  int16_t getFipVolts(int16_t); // getting the first integer part of the measured voltage
  int16_t getSipVolts(int16_t); // getting the second integer part of the measured voltage
  // data
};

#endif