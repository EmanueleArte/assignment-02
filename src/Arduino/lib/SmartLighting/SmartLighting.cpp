#include "SmartLighting.h"
#include <Arduino.h>

#define PIR_PIN 7
#define LIGHT_SENSOR_PIN A3
#define LED_A_PIN 6

#define THRESHOLD 600
#define T1 2000

bool t1check();

unsigned long lastPirOn = 0;

SmartLighting::SmartLighting() {
  ledA = new Led(LED_A_PIN);
  p = new Pir(PIR_PIN);
  ls = new LightSensor(LIGHT_SENSOR_PIN, THRESHOLD);
  active = true;
}

void SmartLighting::init(int period) {
  Task::init(period);
  msgService = new MsgServiceClass();
}

void SmartLighting::tick() {
  routine();
}

void SmartLighting::activate() {
  active = true;
}

void SmartLighting::deactivate() {
  active = false;
}

void SmartLighting::routine() {
  if (active) {
    if(p->check()) {
      lastPirOn = millis();
    }
    if(ls->check() || t1check()) {
      ledA->switchOff();
      msgService->sendMsg("SmartLight-off");
    } else {
      ledA->switchOn();
      msgService->sendMsg("SmartLight-on");
    }
  } else {
    ledA->switchOff();
    msgService->sendMsg("SmartLight-off");
  }
}

// returns true if the timer was never started or if T1 has elapsed
bool t1check() {
  if(lastPirOn == 0) {
    return true;
  }
  return millis() > lastPirOn + T1;
}