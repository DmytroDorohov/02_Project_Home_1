/*
Описание библиотеки
*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Project_OLED.h>

const int8_t SCREEN_WIDTH = 128; // OLED display width, in pixels
const int8_t SCREEN_HEIGHT = 64; // OLED display height, in pixels
const int8_t OLED_RESET = -1;    // Reset pin # (or -1 if sharing Arduino reset pin)
const int8_t ADDR_OLED = 0x3C;   // Oled address on I2C

Adafruit_SSD1306 oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**
 * Constructor
 */
Oled::Oled(void) {}

/**
 * Function of show logo
 */
void Oled::logo(String ver)
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
  showPosText(20, 10, "ADS:");
  showPosText(20, 20, "BME:");
  showPosText(20, 30, "RTC:");
  showPosText(20, 40, "FLASH:");
  showPosText(20, 50, "MQ:");
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
    oled.print(mas[5 + i]);
    oled.print(str[4]);
    oled.print(mas[6 + i]);
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