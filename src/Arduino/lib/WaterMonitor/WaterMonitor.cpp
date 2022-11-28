#include "WaterMonitor.h"

#define POT_PIN A2
#define BUTTON_PIN 8
#define LED_B_PIN 10
#define LED_C_PIN 5
#define MOTOR_PIN 9
#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 13

#define BLINK_PERIOD 2000
#define MIN_DEGREES 0
#define MAX_DEGREES 180

void blinkLed(Led* pin, unsigned period);
char* getSituation();
char* getWaterLevel(Sonar* s);
char* getValveDegrees(Motor* m);

#define STATE_NUMBER 3
#define STATE_NAME_LENGTH 10

char stateName[STATE_NUMBER][STATE_NAME_LENGTH] = { "Normal", "Pre-alarm", "Alarm" };

char situation[30];
char buffer[30];

WaterMonitor::WaterMonitor() {
  ledB = new Led(LED_B_PIN);
  ledC = new Led(LED_C_PIN);
  m = new Motor(MOTOR_PIN);
  pot = new Potentiometer(POT_PIN);
  s = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  b = new Button(BUTTON_PIN);
  lcd = new Lcd();
  manualMode = false;
  state = NONE;
  lcd->init();
}

void WaterMonitor::init(int period) {
  Task::init(period);
  msgService = new MsgServiceClass();
}

void WaterMonitor::tick() {
  routine();
}

void WaterMonitor::routine() {
  s->check();
  if (s->getWaterLevel() > WL1) {
    normalState();
  } else if(s->getWaterLevel() > WL2 && s->getWaterLevel() <= WL1) {
    preAlarmState();
  } else {
    alarmState();
  }
  msgService->sendMsg(s->getWaterLevel());
}

void WaterMonitor::normalState() {
  if (state != NORMAL) {
    this->init(PE_NORMAL);
    state = NORMAL;
    msgService->sendMsg(stateName[state]);
    manualMode = false;
    ledB->switchOn();
    ledC->switchOff();
    lcd->turnOff();
    lcd->clearAll();
    m->setValveDegrees(MIN_DEGREES);
  }
}

void WaterMonitor::preAlarmState() {
  if (state != PRE_ALARM) {
    this->init(PE_PRE_ALARM);
    state = PRE_ALARM;
    msgService->sendMsg(stateName[state]);
    manualMode = false;
    ledB->switchOn();
    m->setValveDegrees(MIN_DEGREES);
    lcd->turnOn();
    lcd->clear(2);
    lcd->print(getSituation(), 0);
    strcpy(buffer, "Water level: ");
    lcd->print(buffer, 1);
  }
  lcd->print(getWaterLevel(s), 1, 13);
  blinkLed(ledC, BLINK_PERIOD);
}

void WaterMonitor::alarmState() {
  if (state != ALARM) {
    this->init(PE_ALARM);
    state = ALARM;
    msgService->sendMsg(stateName[state]);
    ledB->switchOff();
    ledC->switchOn();
    lcd->turnOn();
    lcd->print(getSituation(), 0);
    strcpy(buffer, "Water level: ");
    lcd->print(buffer, 1);
    strcpy(buffer, "Valve degrees: ");
    lcd->print(buffer, 2);
  }
  lcd->print(getWaterLevel(s), 1, 13);
  if (b->isPressed()) {
    manualMode = !manualMode;
  }
  if (!manualMode) {
    m->setValveDegrees(map(s->getWaterLevel(), WLMAX, WL2, MAX_DEGREES, MIN_DEGREES));
  } else {
    m->setValveDegrees(map(pot->getValveDegrees(), 0, 1023, MAX_DEGREES, MIN_DEGREES));
  }
  lcd->print(getValveDegrees(m), 2, 15);
}

// Returns a string with the current situation
char* WaterMonitor::getSituation() {
  strcpy(situation, "Situation: ");
  strcat(situation, stateName[state]);
  return situation;
}

// Make the given led blink at the given period
void blinkLed(Led* led, unsigned period) {
  if (millis() % (period * 2) < period) {
    led->switchOn();
  } else {
    led->switchOff();
  }
}

// Returns a string with the current water level
char* getWaterLevel(Sonar* s) {
  char level[5];
  sprintf(level, "%d", s->getWaterLevel());
  strcpy(buffer, level);
  return buffer;
}

// Returns the current valve opening degrees
char* getValveDegrees(Motor* m) {
  char degrees[4];
  sprintf(degrees, "%d", m->getValveDegrees());
  strcpy(buffer, degrees);
  return buffer;
}