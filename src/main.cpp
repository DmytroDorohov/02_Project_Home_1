#include <Arduino.h>
#include <Wire.h>
#include <Project_OLED.h>
#include <Project_Sensors.h>
#include <Project_WiFi.h>
// #include <Project_Test.h>

const char *VERSION = "0.7";            // Version project
const char *WIFI_SSID = "TP-Link_D445"; // WiFi login
const char *WIFI_PASS = "40581330";     // WiFi password
const int8_t ADDR_ADS = 0x48;           // ADS1115 address on I2C
const int8_t ADDR_BME = 0x76;           // BME280 address on I2C (0x77h or 0x76h)
const int8_t ADDR_RTC = 0x68;           // DS1307 address on I2C
const int8_t ADDR_AT = 0x50;            // AT24 address on I2C
const int8_t ADDR_OLED = 0x3C;          // Oled address on I2C
const int8_t SCREEN_WIDTH = 128;        // Oled display width, in pixels
const int8_t SCREEN_HEIGHT = 64;        // Oled display height, in pixels
const int8_t OLED_RESET = -1;           // Reset pin # (or -1 if sharing Arduino reset pin)
const int8_t PIN_MQ_IN = D5;            // MQ135 input pin
const int8_t PIN_MQ_OUT = D6;           // MQ135 output pin

static int16_t dataSensors[18]; // data array
static Oled Disp;               // class from Project_OLED
static Sensors Sens;            // class from Project_Sensors
static WF Wf;                   // class from Project_WiFi

void setup()
{
  // Start
  Serial.begin(115200);
  Wire.begin();

  // Initialization oled display and show logo
  Disp.logo(ADDR_OLED, SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET, VERSION);
  delay(3000);

  // Initialization sesors
  Sens.initSensors(ADDR_ADS, ADDR_BME, ADDR_RTC, ADDR_AT, PIN_MQ_IN, PIN_MQ_OUT, &Disp);
  delay(3000);

  // Conecting to WiFi
  Wf.initWiFi(WIFI_SSID, WIFI_PASS, &Disp);
  delay(3000);
}

void loop()
{
  // scanWire(); // scan I2C
  Sens.getData(dataSensors);
  Disp.showFirstPage(dataSensors, Sens.getDate(), Sens.getTime());
  delay(15000);
  Disp.showSecondPage(dataSensors, Sens.getDate(), Sens.getTime());
  delay(15000);
  // третья страница со статусом датчиков
  for (int8_t i = 0; i < 18; i++)
  {
    Serial.print("Data[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(dataSensors[i]);
  }
  Serial.println("------");
}