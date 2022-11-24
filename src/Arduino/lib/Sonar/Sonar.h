#ifndef __SONAR__
#define __SONAR__

#include <Arduino.h>
#include <Ultrasonic.h>

class Sonar {
 
public: 
  Sonar(int pin1, int pin2);
  int getWaterLevel();

private:
  Ultrasonic* sonar;
};

#endif