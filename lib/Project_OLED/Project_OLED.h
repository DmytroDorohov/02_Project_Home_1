/*
Описание библиотеки
*/

#ifndef Project_OLED_h
#define Project_OLED_h
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Oled
{
public:
  Oled(void);                            // constructor
  void logo(String);                     // function of show logo
  void showInitWifi(int);                // function of show initialization WiFi
  void showInitSensors(void);            // function of show initialization sensors
  void showInitSensors(int8_t, boolean); //
  void showFirstPage(int16_t *);         // function of show first information page
  void showSecondPage(int16_t *);        // function of show second information page
private:
  // functions
  void showHeaderPage(int16_t *);           // function of show header information in pages
  void showPosText(int8_t, int8_t, String); // function of show text in position
  // data
};

#endif