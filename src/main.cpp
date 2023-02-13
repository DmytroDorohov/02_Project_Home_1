#include <Arduino.h>
#include <Wire.h>
#include <Project_OLED.h>
#include <Project_Sensors.h>
#include <Project_WiFi.h>
// #include <Project_Test.h>

const char *VERSION = "0.9";            // Version project
const char *WIFI_SSID = "TP-Link_D445"; // WiFi login
const char *WIFI_PASS = "40581330";     // WiFi password

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
  Disp.logo(VERSION);
  delay(3000);

  // Conecting to WiFi
  Wf.initWiFi(WIFI_SSID, WIFI_PASS, &Disp);
  delay(3000);

  // Synchronizing
  Wf.synchroTimeDate();

  // Initialization sesors
  Sens.initSensors(&Disp);
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