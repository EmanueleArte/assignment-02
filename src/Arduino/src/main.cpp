#include <Arduino.h>
#include <Wire.h>
#include "Scheduler.h"
#include "SmartLighting.h"
#include "WaterMonitor.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);

  //disabilitare sistema luci in alarm
  Task* smartLighting = new SmartLighting();
  smartLighting->init(200);
  Task* waterMonitor = new WaterMonitor();
  waterMonitor->init(PE_NORMAL);

  sched.addTask(smartLighting);
  sched.addTask(waterMonitor);
}

void loop() {
  sched.schedule();
  //waterMonitor->tick();
  //delay(200);
}