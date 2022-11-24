#include <Arduino.h>
#include <Wire.h>
#include "Scheduler.h"
#include "SmartLighting.h"
#include "WaterMonitor.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);

  Task* smartLighting = new SmartLighting();
  smartLighting->init(200);
  Task* waterMonitor = new WaterMonitor();
  waterMonitor->init(500);

  sched.addTask(smartLighting);
  sched.addTask(waterMonitor);
}

void loop() {
  sched.schedule();
}