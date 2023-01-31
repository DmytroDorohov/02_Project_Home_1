/*
Описание библиотеки
*/

#ifndef Project_OLED_h
#define Project_OLED_h
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void logo(String);              // function of show logo
void showInitWifi(int);         // function of show initialization WiFi
void showInitSensors(int);      // function of show initialization sensors
void showFirstPage(int16_t *);  // function of show first information page
void showSecondPage(int16_t *); // function of show second information page

extern Adafruit_SSD1306 oled;
#endif