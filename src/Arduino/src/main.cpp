#include <Arduino.h>
#include <Wire.h>
#include "Scheduler.h"
#include "SmartLighting.h"

//Ultrasonic us(12, 13);
Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);

  Task* smartLighting = new SmartLighting();
  smartLighting->init(200);

  sched.addTask(smartLighting);
}

void loop() {
  sched.schedule();
}