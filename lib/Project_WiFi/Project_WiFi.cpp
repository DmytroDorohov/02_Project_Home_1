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
  _dp.showInitWifi();
  if (!WiFi.begin(_ssid, _pass))
    _dp.showInitWifi(10, 40, "ERROR init WiFi");
  else
  {
    _dp.showInitWifi(10, 20, "Conecting WiFi");
    return;
  }
  for (int8_t i = 1; i <= 42; i++)
  {
    _dp.showInitWifi(i);
    delay(500);
    if (WiFi.status() == WL_CONNECTED)
    {
      _dp.showInitWifi(10, 52, WiFi.localIP().toString());
      break;
    }
    else if (i == 42)
    {
      _dp.showInitWifi(10, 52, "ERROR conect");
      break;
    }
  }
}