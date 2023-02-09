/*
Описание библиотеки
*/

#ifndef Project_Sensors_h
#define Project_Sensors_h
#include <Arduino.h>

#define AT_PAGE 32       // page size AT24C32
#define AT_TEST_BYTE 0   // test byte in AT24C32 memory address
#define AT_HB_QUANTITY 1 // high byte of the number of records in AT24C32 memory address
#define AT_LB_QUANTITY 2 // low byte of the number of records in AT24C32 memory address
#define AT_BEGIN_ADDR 8  // the address of the beginning of records in AT24C32 memory

class Sensors
{
public:
  Sensors(void);                                                            // constructor
  void initSensors(int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, Oled *); // initialization sensors
  void getData(int16_t *);                                                  // get data in massiv from sensors
  String getDate(void);                                                     // get RTC date
  String getTime(void);                                                     // get RTC time
private:
  int16_t getFipVolts(int16_t);     // getting the first integer part of the measured voltage
  int16_t getSipVolts(int16_t);     // getting the second integer part of the measured voltage
  void writeByteAT(uint16_t, byte); // write byte in AT24
  byte readByteAT(uint16_t);        // read byte from AT24
  int8_t _addr_ads, _addr_bme, _addr_ds, _addr_at;
  int8_t _pin_mq_in, _pin_mq_out;
};

#endif