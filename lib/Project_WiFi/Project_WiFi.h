/*
Описание библиотеки
*/

#ifndef Project_WiFi_h
#define Project_WiFi_h
#include <Arduino.h>

class WF
{
public:
  WF(String, String);  // constructor
  void initWiFi(void); // function of initialization WiFi conection
private:
  // functions
  // data
  String _ssid, _pass;
};

#endif