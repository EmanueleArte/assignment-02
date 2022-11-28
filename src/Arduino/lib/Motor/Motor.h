#ifndef __MOTOR__
#define __MOTOR__

#include <Servo.h>

class Motor {
 
public: 
  Motor(int pin);
  void setValveDegrees(int degrees);
  int getValveDegrees();

private:
  Servo motor;
  int valveDegrees;

};

#endif