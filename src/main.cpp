#include <Arduino.h>
#include <Wire.h>
#include <Project_OLED.h>
#include <Project_Sensors.h>
#include <Project_WiFi.h>

const char *VERSION = "0.11";           // Version project
const char *WIFI_SSID = "TP-Link_D445"; // WiFi login
const char *WIFI_PASS = "40581330";     // WiFi password
const int8_t TRANS_PERIOD = 5;          // transmission period time minutes

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

  // Connecting to WiFi
  Wf.connectWiFi(WIFI_SSID, WIFI_PASS, false, &Disp);

  // Initialization sesors
  Sens.initSensors(&Disp);
  Sens.getData(dataSensors);
  delay(5000);
}

void loop()
{
  Disp.showFirstPage(dataSensors);
  delay(20000);
  Disp.showSecondPage(dataSensors);
  delay(20000);

  if (Wf.transmissionTime(TRANS_PERIOD))
  {
    Sens.getData(dataSensors);
    Wf.sendData(dataSensors, WIFI_SSID, WIFI_PASS, &Disp);
  }
}