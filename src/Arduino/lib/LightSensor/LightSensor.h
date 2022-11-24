#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

#include "Sensor.h"

class LightSensor : public Sensor {

public:
  LightSensor(int pin, int threshold);
  bool check();

private:
  int pin;
  int threshold;
};

#endif