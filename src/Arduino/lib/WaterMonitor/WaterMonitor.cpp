#include "WaterMonitor.h"
#include <Arduino.h>

#define POT_PIN A2
#define BUTTON_PIN 8
#define LED_B_PIN 9
#define LED_C_PIN 10
#define MOTOR_PIN 11
#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 13

#define WL1 40
#define WL2 20
#define WLMAX 0
#define PE_NORMAL 500
#define PE_PRE_ALARM 200
#define PE_ALARM 100

#define BLINK_PERIOD 2000
#define MIN_DEGREES 0
#define MAX_DEGREES 180

State state;
enum State { NORMAL, PRE_ALARM, ALARM };

unsigned long lastPirOn = 0;

WaterMonitor::WaterMonitor() {
  this->ledB = new Led(LED_B_PIN);
  this->ledC = new Led(LED_C_PIN);
  this->m = new Motor(MOTOR_PIN);
  this->pot = new Potentiometer(POT_PIN);
  this->s = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  this->b = new Button(BUTTON_PIN);
  this->lcd = new Lcd();
  this->msgService = new MsgServiceClass();
}

void WaterMonitor::init(int period) {
  Task::init(period);
}  

void WaterMonitor::tick() {
  routine();
}

void WaterMonitor::routine() {
  if(s->getWaterLevel() > WL1) {
    normalState();
  } else if(s->getWaterLevel() > WL2 && s->getWaterLevel() <= WL1) {
    preAlarmState();
  } else {
    alarmState();
  }
}

void WaterMonitor::normalState() {
  state = NORMAL;
  ledB->switchOn();
  ledC->switchOff();
  m->setValveDegrees(MIN_DEGREES);
}

void WaterMonitor::preAlarmState() {
  state = PRE_ALARM;
  ledB->switchOn();
  blinkLed(ledC, BLINK_PERIOD);
  m->setValveDegrees(MIN_DEGREES);
}

void WaterMonitor::alarmState() {
  state = ALARM;
  ledB->switchOff();
  ledC->switchOn();
  m->setValveDegrees(map(s->getWaterLevel(), WLMAX, WL2, MAX_DEGREES, MIN_DEGREES));
}

void blinkLed(Led* led, int period) {
  if(millis() % (period * 2) < period) {
    led->switchOn();
  } else {
    led->switchOff();
  }
}