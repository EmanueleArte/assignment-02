#include "Potentiometer.h"
#include <Arduino.h>

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);     
} 
  
int Potentiometer::getValveDegrees(){
  return map(analogRead(pin), 0, 1023, 0, 180);
}