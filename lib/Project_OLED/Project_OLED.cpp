/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Project_OLED.h>

static Adafruit_SSD1306 oled;

/**
 * Constructor
 */
Oled::Oled(void) {}

/**
 * Function of show logo
 */
void Oled::logo(int8_t _addr, int8_t _sw, int8_t _sh, int8_t _or, const char *ver)
{
  oled = Adafruit_SSD1306(_sw, _sh, &Wire, _or);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  oled.begin(SSD1306_SWITCHCAPVCC, _addr);
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
}

/**
 * Function of show initialization WiFi
 */
void Oled::showInitWifi(void)
{
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  showPosText(0, 0, "Initialization WiFi");
}

void Oled::showInitWifi(int8_t a)
{
  oled.fillRect(1, 40, 3 * a, 5, SSD1306_WHITE);
  oled.display();
}

void Oled::showInitWifi(int8_t x, int8_t y, String s)
{
  showPosText(x, y, s);
}

/**
 * Function of show initialization sensors
 */
void Oled::showInitSensors(void)
{
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  showPosText(0, 0, "Init sensors");
  showPosText(20, 12, "ADS:");
  showPosText(20, 22, "BME:");
  showPosText(20, 32, "RTC:");
  showPosText(20, 42, "FLASH:");
  showPosText(20, 52, "MQ:");
}

void Oled::showInitSensors(int8_t y, boolean b)
{
  if (!b)
    showPosText(60, y, "OK");
  else
    showPosText(60, y, "ERROR");
}

/**
 * Function of show first information page
 */
void Oled::showFirstPage(int16_t *mas, String date, String time)
{
  _date = date;
  _time = time;
  showHeaderPage();
  String str[] = {"Temp = ", "Pres = ", "Humi = ", "Qual = ", " C", " mmHg", " %", " %"};
  for (int8_t i = 0; i < 4; i++)
  {
    oled.setCursor(10, 12 * (i + 1));
    oled.print(str[i]);
    oled.print(mas[13 + i]);
    oled.print(str[4 + i]);
  }
  oled.display();
}

/**
 * Function of show second information page
 */
void Oled::showSecondPage(int16_t *mas, String date, String time)
{
  _date = date;
  _time = time;
  showHeaderPage();
  String str[] = {"A0 = ", "A1 = ", "A2 = ", "A3 = ", ".", " V"};
  for (int8_t i = 0; i < 4; i++)
  {
    oled.setCursor(10, 12 * (i + 1));
    oled.print(str[i]);
    oled.print(mas[5 + i * 2]);
    oled.print(str[4]);
    oled.print(mas[6 + i * 2]);
    oled.print(str[5]);
  }
  oled.display();
}

/**
 * Function of show header information in pages
 */
void Oled::showHeaderPage(void)
{
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.print(_date);
  oled.setCursor(80, 0);
  oled.print(_time);
  oled.display();
}

/**
 * Function of show text in position
 */
void Oled::showPosText(int8_t x, int8_t y, String t)
{
  oled.setCursor(x, y);
  oled.print(t);
  oled.display();
}