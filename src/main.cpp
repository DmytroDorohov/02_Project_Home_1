#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Project_OLED.h>
#include <Project_Test.h>
#include <Project_Sensors.h>

const String VERSION = "0.3";           // Version project
const char *WIFI_SSID = "TP-Link_D445"; // WiFi login
const char *WIFI_PASS = "40581330";     // WiFi password

int16_t dataSensors[18];

void setup()
{
  // Start
  Serial.begin(115200);
  Wire.begin();
  logo(VERSION); // Show logo in start

  // Conecting to WiFi
  if (!WiFi.begin(WIFI_SSID, WIFI_PASS))
    showInitWifi(0);
  showInitWifi(1);
  for (int i = 1; i <= 42; i++)
  {
    showInitWifi(2);
    delay(500);
    if (WiFi.status() == WL_CONNECTED)
    {
      showInitWifi(3);
      break;
    }
    else if (i == 42)
    {
      showInitWifi(40);
      break;
    }
  }
  delay(2000);

  // Initialization sesors
  initSensors();
  delay(2000);
}

void loop()
{
  scanWire(); // сканирование I2C линии
  getData(dataSensors);
  showFirstPage(dataSensors);
  delay(3000);
  showSecondPage(dataSensors);
  delay(3000);
  for (int i = 0; i < 18; i++)
  {
    Serial.println(dataSensors[i]);
  }
  delay(3000); // задержка
}