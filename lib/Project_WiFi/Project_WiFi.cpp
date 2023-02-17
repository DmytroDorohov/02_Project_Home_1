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
 * return false if connection error, return true if connection succeeded
 */
boolean WF::connectWiFi(const char *_ssid, const char *_pass, boolean _st, Oled *_disp)
{
  _disp->showInitWifi();
  if (!WiFi.begin(_ssid, _pass))
  {
    _disp->showInitWifi(10, 40, "ERROR init WiFi");
    return false;
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
      return false;
    }
  }
  synchroTimeDate();

  // init first time
  if (!_st)
  {
    // init first time transmission
    _ftt = (minute() / 10) * 10;
    Serial.print("first time transmission = ");
    Serial.println(_ftt);
    WiFi.disconnect();
  }

  return true;
}

/**
 * function of synchronizing time fnd date with server
 * setTime(hour,minute,sec,day,month,year)
 */
void WF::synchroTimeDate(void)
{
  setTime(14, 8, 45, 13, 2, 2023);
}

/**
 * Function of transmission time checks
 */
boolean WF::transmissionTime(int8_t _period)
{
  // send every '_period' minutes
  if (minute() == (_ftt + _period))
  {
    _ftt = (minute() / 10) * 10;
    return true;
  }
  else
    return false;
}

/**
 * Function of send data in server
 */
void WF::sendData(int16_t *mas, const char *_ssid, const char *_pass, Oled *_disp)
{
  _result_transmition = connectWiFi(_ssid, _pass, true, _disp);

  // sending delayed data
  if (_count_send_error > 0)
  {
    do
    {
      for (uint8_t i = 0; i <= sizeof(mas); i++)
      {
        Serial.print(dataSensorsNoSend[_count_send_error][i]);
        Serial.print("   ");
      }
      Serial.println();
      _result_transmition = true;

      if (!_result_transmition)
        break;
      _count_send_error--;
    } while (_count_send_error > 0);
  }
  Serial.println("------");

  // sending instant data
  if (_result_transmition)
  {
    // test code - true transmition
    for (uint8_t i = 0; i <= sizeof(mas); i++)
    {
      Serial.print(mas[i]);
      Serial.print("   ");
    }
    Serial.println("------");
    _result_transmition = true;
  }

  // if there is an error sending data, then write to the data delay array
  if (!_result_transmition)
  {
    for (uint8_t i = 0; i <= sizeof(mas); i++)
    {
      dataSensorsNoSend[_count_send_error][i] = mas[i];
    }
    _count_send_error++;
  }
  WiFi.disconnect();
}