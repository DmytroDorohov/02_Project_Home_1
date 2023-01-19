#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Project_OLED.h>
#include <Project_Test.h>
#include <Project_Sensors.h>

const String VERSION = "0.1";           // Version project
const char *WIFI_SSID = "TP-Link_D445"; // WiFi login
const char *WIFI_PASS = "40581330";     // WiFi password
const int ADDR_ADS = 0x10;              // ADS1115 address on I2C
const int ADDR_BME = 0x10;              // BME280 address on I2C
const int ADDR_MQ = 0x10;               // MQ135 address on I2C
const int ADDR_RTC = 0x10;              // TinyRTC DS1307 address on I2C
const int ADDR_MEM = 0x10;              // TinyRTC AT24C address on I2C

int dataSensors[10];

void setup()
{
  // Start
  Serial.begin(115200);
  Wire.begin();
  logo(VERSION); // Show logo in start

  // Conecting to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  showInitWifi(1);
  for (int i = 1; i <= 40; i++)
  {
    showInitWifi(2);
    delay(500);
    if (WiFi.status() == WL_CONNECTED)
    {
      showInitWifi(3);
      break;
    }
    else if (i == 40)
    {
      showInitWifi(40);
      break;
    }
  }

  // Initialization sesors
  initSensors();
}

void loop()
{
  delay(5000); // задержка
  scanWire();  // сканирование I2C линии
  testingOLED();
  getData(dataSensors);
  for (int i = 0; i < 10; i++)
  {
    Serial.println(dataSensors[i]);
  }
}