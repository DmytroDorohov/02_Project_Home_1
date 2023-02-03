#include <Arduino.h>
#include <Project_OLED.h>
// #include <Project_Test.h>
#include <Project_Sensors.h>
#include <Project_WiFi.h>

const String VERSION = "0.5";            // Version project
const String WIFI_SSID = "TP-Link_D445"; // WiFi login
const String WIFI_PASS = "40581330";     // WiFi password
const int8_t ADDR_ADS = 0x48;            // ADS1115 address on I2C
const int8_t ADDR_BME = 0x76;            // BME280 address on I2C (0x77h or 0x76h)
const int8_t ADDR_RTC = 0x68;            // DS1307 address on I2C
const int8_t ADDR_AT = 0x50;             // AT24 address on I2C
const int8_t PIN_MQ_IN = D7;             // MQ135 input pin
const int8_t PIN_MQ_OUT = D8;            // MQ135 output pin

int16_t dataSensors[18];
Oled Disp;                                                                  // class from Project_OLED
Sensors Sens(ADDR_ADS, ADDR_BME, ADDR_RTC, ADDR_AT, PIN_MQ_IN, PIN_MQ_OUT); // class from Project_Sensors
WF Wf(WIFI_SSID, WIFI_PASS);                                                // class from Project_WiFi

void setup()
{
  // Start
  Serial.begin(115200);
  Wire.begin();
  Disp.logo(VERSION); // Show logo in start

  // Conecting to WiFi
  Wf.initWiFi();
  delay(2000);

  // Initialization sesors
  Sens.initSensors();
  delay(5000);
}

void loop()
{
  // scanWire(); // scan I2C
  Sens.getData(dataSensors);
  Disp.showFirstPage(dataSensors, Sens.getDate(), Sens.getTime());
  delay(5000);
  Disp.showSecondPage(dataSensors, Sens.getDate(), Sens.getTime());
  delay(5000);
  // третья страница со статусом датчиков
  for (int8_t i = 0; i < 18; i++)
  {
    Serial.println(dataSensors[i]);
  }
  delay(3000);
}