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
  Oled(void);                                     // constructor
  void logo(String);                              // function of show logo
  void showInitWifi(void);                        // function of show initialization WiFi
  void showInitWifi(int8_t);                      //
  void showInitWifi(int8_t, int8_t, String);      //
  void showInitSensors(void);                     // function of show initialization sensors
  void showInitSensors(int8_t, boolean);          //
  void showFirstPage(int16_t *, String, String);  // function of show first information page
  void showSecondPage(int16_t *, String, String); // function of show second information page
private:
  // functions
  void showHeaderPage();                    // function of show header information in pages
  void showPosText(int8_t, int8_t, String); // function of show text in position
  // data
  String _date, _time;
};

#endif