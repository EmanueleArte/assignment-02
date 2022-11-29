#ifndef __SONAR__
#define __SONAR__

#include <Arduino.h>
#include <Ultrasonic.h>
#include "Sensor.h"

class Sonar : public Sensor {
 
public: 
  Sonar(int pin1, int pin2);
  bool check();
  int getData();

private:
  Ultrasonic* sonar;
  int waterLevel;

};

#endif