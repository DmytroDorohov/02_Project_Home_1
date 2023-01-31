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
  oled.setCursor(40, 55);
  oled.print("ver ");
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
    oled.println("\n");
    oled.println("Conected: ");
    oled.println();
    oled.println(WiFi.localIP());
    oled.display();
    break;
  default:
    oled.println("\n");
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
    oled.println();
    oled.display();
    break;
  case 10:
    oled.println("ERROR init ADS module");
    oled.println();
    oled.display();
    break;
  case 11:
    oled.println("ADS module OK");
    oled.println();
    oled.display();
    break;
  case 20:
    oled.println("ERROR init BME module");
    oled.println();
    oled.display();
    break;
  case 21:
    oled.println("BME module OK");
    oled.println();
    oled.display();
    break;
  case 30:
    oled.println("ERROR init MQ module");
    oled.println();
    oled.display();
    break;
  case 31:
    oled.println("MQ module OK");
    oled.println();
    oled.display();
    break;
  default:
    oled.println("ERROR sensor");
    oled.display();
    break;
  }
}

void showFirstPage(int16_t *mas)
{
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  //
  oled.print(mas[0]);
  oled.print(".");
  oled.print(mas[1]);
  oled.print(".");
  oled.print(mas[2]);
  oled.print("    ");
  oled.print(mas[3]);
  oled.print(":");
  oled.print(mas[4]);
  oled.println();
  //
  oled.setCursor(10, 12);
  oled.print("Temp = ");
  oled.print(mas[13]);
  oled.print(" 'C");
  oled.setCursor(10, 24);
  oled.print("Pres = ");
  oled.print(mas[14]);
  oled.print(" mmHg");
  oled.setCursor(10, 36);
  oled.print("Humi = ");
  oled.print(mas[15]);
  oled.print(" %");
  oled.setCursor(10, 48);
  oled.print("Qual = ");
  oled.print(mas[16]);
  oled.print(" %");
  oled.display();
}

void showSecondPage(int16_t *mas)
{
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  //
  oled.print(mas[0]);
  oled.print(".");
  oled.print(mas[1]);
  oled.print(".");
  oled.print(mas[2]);
  oled.print("    ");
  oled.print(mas[3]);
  oled.print(":");
  oled.print(mas[4]);
  oled.println();
  //
  oled.setCursor(10, 12);
  oled.print("A0 = ");
  oled.print(mas[5]);
  oled.print(".");
  oled.print(mas[6]);
  oled.print(" V");
  oled.setCursor(10, 24);
  oled.print("A1 = ");
  oled.print(mas[7]);
  oled.print(".");
  oled.print(mas[8]);
  oled.print(" V");
  oled.setCursor(10, 36);
  oled.print("A2 = ");
  oled.print(mas[9]);
  oled.print(".");
  oled.print(mas[10]);
  oled.print(" V");
  oled.setCursor(10, 48);
  oled.print("A3 = ");
  oled.print(mas[11]);
  oled.print(".");
  oled.print(mas[12]);
  oled.print(" V");
  oled.display();
}