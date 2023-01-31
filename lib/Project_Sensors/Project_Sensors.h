/*
Описание библиотеки
*/

#ifndef Project_Sensors_h
#define Project_Sensors_h
#include <Arduino.h>

void initSensors();           // initialization sensors
void getData(int16_t *);      // get data in massiv from sensors
int16_t getFipVolts(int16_t); // getting the first integer part of the measured voltage
int16_t getSipVolts(int16_t); // getting the second integer part of the measured voltage

#endif