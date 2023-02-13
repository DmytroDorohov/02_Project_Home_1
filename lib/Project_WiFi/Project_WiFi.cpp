/*
Описание библиотеки
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <Project_OLED.h>
#include <Project_WiFi.h>

/**
 * Constructor
 */
WF::WF(void) {}

/**
 * Initialization of WiFi conection
 */
void WF::initWiFi(const char *_ssid, const char *_pass, Oled *_disp)
{
  _disp->showInitWifi();
  if (!WiFi.begin(_ssid, _pass))
  {
    _disp->showInitWifi(10, 40, "ERROR init WiFi");
    return;
  }
  else
    _disp->showInitWifi(10, 20, "Conecting WiFi");
  for (int8_t i = 1; i <= 42; i++)
  {
    _disp->showInitWifi(i);
    delay(500);
    if (WiFi.status() == WL_CONNECTED)
    {
      _disp->showInitWifi(42);
      _disp->showInitWifi(10, 52, WiFi.localIP().toString());
      break;
    }
    else if (i == 42)
    {
      _disp->showInitWifi(10, 52, "ERROR conect");
      break;
    }
  }
}

/**
 * function of synchronizing time fnd date with server
 *
 */
void WF::synchroTimeDate(void)
{
  setTime(14, 10, 45, 13, 2, 2023);
}