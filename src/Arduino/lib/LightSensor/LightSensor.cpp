#include "LightSensor.h"
#include <Arduino.h>

LightSensor::LightSensor(int pin, int threshold) {
  this->pin = pin;
  pinMode(this->pin, INPUT);
  this->threshold = threshold > 1023 ? 1023 : threshold;
}

bool LightSensor::check() {
  return analogRead(this->pin) > this->threshold;
}