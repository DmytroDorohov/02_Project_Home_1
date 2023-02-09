/*
Описание библиотеки
*/

#ifndef Project_WiFi_h
#define Project_WiFi_h
#include <Arduino.h>

class WF
{
public:
  WF(void);                                          // constructor
  void initWiFi(const char *, const char *, Oled *); // function of initialization WiFi conection
private:
};

#endif