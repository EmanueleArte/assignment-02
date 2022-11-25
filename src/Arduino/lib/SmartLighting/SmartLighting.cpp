#include "SmartLighting.h"
#include <Arduino.h>

#define PIR_PIN 7
#define LIGHT_SENSOR_PIN A3
#define LED_A_PIN 6

#define THRESHOLD 400
#define T1 2000

bool t1check();

unsigned long lastPirOn = 0;

SmartLighting::SmartLighting() {
  ledA = new Led(LED_A_PIN);
  p = new Pir(PIR_PIN);
  ls = new LightSensor(LIGHT_SENSOR_PIN, THRESHOLD);
}

void SmartLighting::init(int period) {
  Task::init(period);
}  

void SmartLighting::tick() {
  routine();
}

void SmartLighting::routine() {
  if(p->check()) {
    lastPirOn = millis();
  }
  if(ls->check() || t1check()) {
    ledA->switchOff();
  } else {
    ledA->switchOn();
  }
}

// returns true if the timer was never started or if T1 has elapsed
bool t1check() {
  if(lastPirOn == 0) {
    return true;
  }
  return millis() > lastPirOn + T1;
}