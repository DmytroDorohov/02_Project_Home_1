/*
Описание библиотеки
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Project_OLED.h>
#include <Project_WiFi.h>

Oled _dp;

/**
 * Constructor
 */
WF::WF(String s, String p)
{
  _ssid = s;
  _pass = p;
}

/**
 * Initialization of WiFi conection
 */
void WF::initWiFi(void)
{
  if (!WiFi.begin(_ssid, _pass))
    _dp.showInitWifi(0);
  _dp.showInitWifi(1);
  for (int8_t i = 1; i <= 42; i++)
  {
    _dp.showInitWifi(2);
    delay(500);
    if (WiFi.status() == WL_CONNECTED)
    {
      _dp.showInitWifi(3);
      break;
    }
    else if (i == 42)
    {
      _dp.showInitWifi(40);
      break;
    }
  }
  delay(2000);
}