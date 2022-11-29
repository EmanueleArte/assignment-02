#include <Arduino.h>
#include <Wire.h>
#include "Scheduler.h"
#include "SmartLighting.h"
#include "WaterMonitor.h"
#include "LightActivator.h"
#include "MsgService.h"
#include "Sonar.h"
#include "DataSender.h"

#define SL_PERIOD 500
#define SEND_PERIOD 1000
#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 13

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);

  Sensor* s = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  Task* smartLighting = new SmartLighting();
  smartLighting->init(SL_PERIOD);
  Task* waterMonitor = new WaterMonitor(s);
  waterMonitor->init(PE_NORMAL);
  Task* lightActivator = new LightActivator(smartLighting, waterMonitor, PE_ALARM);
  lightActivator->init(PE_ALARM);
  Task* dataSender = new DataSender(s);
  dataSender->init(SEND_PERIOD);

  sched.addTask(smartLighting);
  sched.addTask(waterMonitor);
  sched.addTask(lightActivator);
  sched.addTask(dataSender);
}

void loop() {
  sched.schedule();
}