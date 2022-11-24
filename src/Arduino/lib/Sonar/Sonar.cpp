#include "Sonar.h"
#include <Arduino.h>

Sonar::Sonar(int pin1, int pin2) {
  sonar = new Ultrasonic(pin1, pin2);
} 
  
int Sonar::getWaterLevel() {
  return sonar->read();
}