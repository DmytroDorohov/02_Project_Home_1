/*
Описание библиотеки
*/

#ifndef Project_Sensors_h
#define Project_Sensors_h
#include <Arduino.h>

void initSensors();  // initialization sensors
void getData(int16_t *); // get data in massiv from sensors

#endif