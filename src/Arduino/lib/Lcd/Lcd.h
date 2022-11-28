#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2C.h>

#define LCD_LINE_LENGTH 20
#define LCD_NUM_LENGTH 5

class Lcd {

public:
  Lcd();
  void init();
  void print(char* text, int line);
  void print(char* text, int line, int col);
  void clear(int line);
  void clear(int line, int col);
  void clearAll();
  void turnOn();
  void turnOff();

private:
  LiquidCrystal_I2C* lcd;
  char lines[4][LCD_LINE_LENGTH];

};

#endif