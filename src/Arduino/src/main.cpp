#include <Arduino.h>
#include <Wire.h>
#include "Scheduler.h"
#include "SmartLighting.h"
#include "WaterMonitor.h"
#include "LightActivator.h"
#include "MsgService.h"

#define SL_PERIOD 500

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);

  Task* smartLighting = new SmartLighting();
  smartLighting->init(SL_PERIOD);
  Task* waterMonitor = new WaterMonitor();
  waterMonitor->init(PE_NORMAL);
  Task* lightActivator = new LightActivator(smartLighting, waterMonitor, PE_ALARM);
  lightActivator->init(SL_PERIOD);

  sched.addTask(smartLighting);
  sched.addTask(waterMonitor);
  sched.addTask(lightActivator);
}

void loop() {
  sched.schedule();
}