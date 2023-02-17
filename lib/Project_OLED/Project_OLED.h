/*
Описание библиотеки
*/

#ifndef Project_OLED_h
#define Project_OLED_h
#include <Arduino.h>

#define ADDR_OLED 0x3C   // Oled address on I2C
#define SCREEN_WIDTH 128 // Oled display width, in pixels
#define SCREEN_HEIGHT 64 // Oled display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

class Oled
{
public:
  Oled(void);                                // constructor
  void logo(const char *);                   // function of show logo
  void showInitWifi(void);                   // function of show initialization WiFi
  void showInitWifi(int8_t);                 //
  void showInitWifi(int8_t, int8_t, String); //
  void showInitSensors(void);                // function of show initialization sensors
  void showInitSensors(int8_t, boolean);     //
  void showFirstPage(int16_t *);             // function of show first information page
  void showSecondPage(int16_t *);            // function of show second information page
private:
  void showHeaderPage();                    // function of show header information in pages
  void showPosText(int8_t, int8_t, String); // function of show text in position
};

#endif