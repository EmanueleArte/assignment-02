#ifndef __PIR__
#define __PIR__

#include "Sensor.h"

class Pir : public Sensor {
public:
  Pir(int pin);
  bool check();
  int getData();

private:
  int pin;

};

#endif