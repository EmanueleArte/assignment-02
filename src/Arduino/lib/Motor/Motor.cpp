#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int pin) {
  motor.attach(pin);
} 
  
void Motor::setValveDegrees(int degrees) {
    motor.write(degrees);
}