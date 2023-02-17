/*
Описание библиотеки
*/

#ifndef Project_WiFi_h
#define Project_WiFi_h
#include <Arduino.h>

class WF
{
public:
  WF(void);                                                         // constructor
  boolean connectWiFi(const char *, const char *, boolean, Oled *); // function of initialization WiFi conection
  boolean transmissionTime(int8_t);                                 // function of transmission time checks
  void sendData(int16_t *, const char *, const char *, Oled *);     // function of send data in server
private:
  void synchroTimeDate(void); // function of synchronizing time fnd date with server
  int8_t _ftt;
  boolean _result_transmition;
  int8_t _count_send_error;
  int16_t dataSensorsNoSend[300][18];
};

#endif