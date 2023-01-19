/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Project_Sensors.h>
#include <Project_OLED.h>

void initSensors(void)
{
  showInitSensors(1);
  showInitSensors(40);
}

void getData(int *mas)
{
  for (int i = 0; i < 10; i++)
  {
    mas[i] = i;
  }
  // some code
}