#include "WaterMonitor.h"
#include <string.h>

#define POT_PIN A2
#define BUTTON_PIN 8
#define LED_B_PIN 10
#define LED_C_PIN 5
#define MOTOR_PIN 9
#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 13

#define BLINK_PERIOD 2000
#define MIN_DEGREES 1
#define MAX_DEGREES 180

void blinkLed(Led* pin, unsigned period);

enum State { NORMAL, PRE_ALARM, ALARM, NONE };
/*map<State, const char*> stateName;
map_init(stateName)
    (NORMAL, "Normal")
    (PRE_ALARM, "Pre-alarm")
    (ALARM, "Alarm")
;*/

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
  manualMode = false;
  state = NONE;
  lcd->init();
}

void WaterMonitor::init(int period) {
  Task::init(period);
}

void WaterMonitor::tick() {
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
    manualMode = false;
    ledB->switchOn();
    ledC->switchOff();
    lcd->turnOff();
    m->setValveDegrees(MIN_DEGREES);
  }
}

void WaterMonitor::preAlarmState() {
  if (state != PRE_ALARM) {
    this->init(PE_PRE_ALARM);
    msgService->sendMsg("Pre-alarm");
    state = PRE_ALARM;
    manualMode = false;
    ledB->switchOn();
    lcd->turnOn();
    m->setValveDegrees(MIN_DEGREES);
  }
  lcd->print("Situation: pre-alarm", 0);
  lcd->print("Water level: ", 1);
  blinkLed(ledC, BLINK_PERIOD);
}

void WaterMonitor::alarmState() {
  if (state != ALARM) {
    this->init(PE_ALARM);
    msgService->sendMsg("Alarm");
    state = ALARM;
    ledB->switchOff();
    ledC->switchOn();
    lcd->turnOn();
  }
  lcd->print("Situation: alarm", 0);
  lcd->print("Water level: ", 1);
  if (b->isPressed()) {
    manualMode = !manualMode;
  }
  if (!manualMode) {
    m->setValveDegrees(map(s->getWaterLevel(), WLMAX, WL2, MAX_DEGREES, MIN_DEGREES));
  } else {
    m->setValveDegrees(map(pot->getValveDegrees(), WLMAX, WL2, MAX_DEGREES, MIN_DEGREES));
  }
}

void blinkLed(Led* led, unsigned period) {
  if (millis() % (period * 2) < period) {
    led->switchOn();
  } else {
    led->switchOff();
  }
}