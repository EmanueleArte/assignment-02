#include <Arduino.h>
#include "Motor.h"

Motor::Motor(int pin) {
  motor.attach(pin);
} 
  
void Motor::setValveDegrees(int degrees) {
  valveDegrees = degrees;
  motor.write(valveDegrees);
  delay(30);
}

int Motor::getValveDegrees() {
  return valveDegrees;
}