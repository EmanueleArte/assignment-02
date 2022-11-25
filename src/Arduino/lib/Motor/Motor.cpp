#include <Arduino.h>
#include "Motor.h"

Motor::Motor(int pin) {
  motor.attach(pin);
} 
  
void Motor::setValveDegrees(int degrees) {
  motor.write(degrees);
  delay(10);
}