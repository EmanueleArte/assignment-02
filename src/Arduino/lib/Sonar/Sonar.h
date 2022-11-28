#ifndef __SONAR__
#define __SONAR__

#include <Arduino.h>
#include <Ultrasonic.h>
#include "Sensor.h"

class Sonar {
 
public: 
  Sonar(int pin1, int pin2);
  void check();
  int getWaterLevel();

private:
  Ultrasonic* sonar;
  int waterLevel;

};

#endif