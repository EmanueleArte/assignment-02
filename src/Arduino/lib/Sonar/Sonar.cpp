#include "Sonar.h"
#include <Arduino.h>

Sonar::Sonar(int pin1, int pin2) {
  sonar = new Ultrasonic(pin1, pin2);
} 

bool Sonar::check() {
  waterLevel = sonar->read();
  return waterLevel > 0;
}

int Sonar::getData() {
  return waterLevel;
}