/*
Описание библиотеки
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Project_OLED.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define ADDR_OLED 0x3C   // Oled address on I2C

Adafruit_SSD1306 oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void logo(String ver)
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  oled.begin(SSD1306_SWITCHCAPVCC, ADDR_OLED);
  oled.clearDisplay();
  oled.setTextSize(3);
  oled.setTextColor(WHITE);
  oled.setCursor(10, 10);
  oled.println("Micrik");
  oled.setTextSize(1);
  oled.setCursor(20, 40);
  oled.println("Project Home 1");
  oled.setCursor(30, 50);
  oled.print("Version ");
  oled.print(ver);
  oled.display();
  delay(5000);
}

void showInitWifi(int i)
{
  switch (i)
  {
  case 0:
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);
    oled.println("ERROR initialization WiFi");
    oled.display();
    break;
  case 1:
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);
    oled.println("Conecting WiFi");
    oled.display();
    break;
  case 2:
    oled.print(".");
    oled.display();
    break;
  case 3:
    oled.println();
    oled.println("Conected: ");
    oled.println(WiFi.localIP());
    oled.display();
    break;
  default:
    oled.println("ERROR Conecting");
    oled.display();
    break;
  }
}

void showInitSensors(int i)
{
  switch (i)
  {
  case 0:
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);
    oled.println("Sensor initialization");
    oled.display();
    break;
  case 10:
    oled.println("ERROR init ADS module");
    oled.display();
    break;
  case 11:
    oled.println("ADS module OK");
    oled.display();
    break;
  case 20:
    oled.println("ERROR init BME module");
    oled.display();
    break;
  case 21:
    oled.println("BME module OK");
    oled.display();
    break;
  case 30:
    oled.println("ERROR init MQ module");
    oled.display();
    break;
  case 31:
    oled.println("MQ module OK");
    oled.display();
    break;
  case 55:
    oled.println("All modules OK");
    oled.display();
    break;
  default:
    oled.println("ERROR sensor ");
    oled.display();
    break;
  }
}

void testingOLED(void)
{
  oled.clearDisplay();
  for (int16_t i = 0; i < oled.height() / 2; i += 2)
  {
    oled.drawRect(i, i, oled.width() - 2 * i, oled.height() - 2 * i, WHITE);
    oled.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }
}