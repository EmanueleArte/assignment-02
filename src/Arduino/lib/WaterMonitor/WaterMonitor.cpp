#include "WaterMonitor.h"

#define POT_PIN A2
#define BUTTON_PIN 8
#define LED_B_PIN 9
#define LED_C_PIN 10
#define MOTOR_PIN 11
#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 13

#define BLINK_PERIOD 2000
#define MIN_DEGREES 0
#define MAX_DEGREES 180

void blinkLed(Led* pin, unsigned period);

enum State { NORMAL, PRE_ALARM, ALARM, NONE };

State state;

WaterMonitor::WaterMonitor() {
  ledB = new Led(LED_B_PIN);
  ledC = new Led(LED_C_PIN);
  m = new Motor(MOTOR_PIN);
  pot = new Potentiometer(POT_PIN);
  s = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  b = new Button(BUTTON_PIN);
  lcd = new Lcd();
  msgService = new MsgServiceClass();
  state = NONE;
  lcd->init();
}

void WaterMonitor::init(int period) {
  Task::init(period);
}

void WaterMonitor::tick() {
  //Serial.println("WaterMonitor::tick()");
  routine();
}

void WaterMonitor::routine() {
  if (s->getWaterLevel() > WL1) {
    normalState();
  } else if(s->getWaterLevel() > WL2 && s->getWaterLevel() <= WL1) {
    preAlarmState();
  } else {
    alarmState();
  }
}

void WaterMonitor::normalState() {
  if (state != NORMAL) {
    this->init(PE_NORMAL);
    msgService->sendMsg("Normal");
    state = NORMAL;
    ledB->switchOn();
    ledC->switchOff();
    m->setValveDegrees(MIN_DEGREES);
  }
}

void WaterMonitor::preAlarmState() {
  if (state != PRE_ALARM) {
    this->init(PE_PRE_ALARM);
    msgService->sendMsg("Pre-alarm");
    state = PRE_ALARM;
    ledB->switchOn();
    m->setValveDegrees(MIN_DEGREES);
  }
  blinkLed(ledC, BLINK_PERIOD);
}

void WaterMonitor::alarmState() {
  if (state != ALARM) {
    this->init(PE_ALARM);
    msgService->sendMsg("Alarm");
    state = ALARM;
    ledB->switchOff();
    ledC->switchOn();
  }
  m->setValveDegrees(map(s->getWaterLevel(), WLMAX, WL2, MAX_DEGREES, MIN_DEGREES));
}

void blinkLed(Led* led, unsigned period) {
  if (millis() % (period * 2) < period) {
    led->switchOn();
  } else {
    led->switchOff();
  }
}