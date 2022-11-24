#ifndef __MOTOR__
#define __MOTOR__

#include <Servo.h>

class Motor {
 
public: 
  Motor(int pin);
  void setValveDegrees(int degrees);

private:
  Servo motor;

};

#endif