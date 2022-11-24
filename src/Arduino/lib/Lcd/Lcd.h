#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2C.h>
#include <string.h>

class Lcd {

public:
  Lcd();
  void init();
  void print(String text, int line);
  void clear(int line);
  void clearAll();
  void turnOn();
  void turnOff();

private:
  LiquidCrystal_I2C* lcd;
  String lines[4];

};

#endif