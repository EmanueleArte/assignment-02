#include "WaterMonitor.h"

#define POT_PIN A2
#define BUTTON_PIN 8
#define LED_B_PIN 10
#define LED_C_PIN 5
#define MOTOR_PIN 9

#define BLINK_PERIOD 2000
#define MIN_DEGREES 0
#define MAX_DEGREES 180
#define MAX_WATER_LEVEL 357

void blinkLed(Led* pin, unsigned period);
char* getWaterLevel(Sensor* s);
char* getValveDegrees(Motor* m);

#define STATE_NUMBER 3
#define STATE_NAME_LENGTH 10

char stateName[STATE_NUMBER][STATE_NAME_LENGTH] = { "Normal", "Pre-alarm", "Alarm" };

char situation[30];
char buffer[30];
char degreesBuffer[5];
int degrees = 0;

WaterMonitor::WaterMonitor(Sensor* s) {
  this->s = s;
  ledB = new Led(LED_B_PIN);
  ledC = new Led(LED_C_PIN);
  m = new Motor(MOTOR_PIN);
  pot = new Potentiometer(POT_PIN);
  b = new Button(BUTTON_PIN);
  lcd = new Lcd();
  manualMode = false;
  remoteManualMode = false;
  state = NONE;
  lcd->init();
}

void WaterMonitor::init(int period) {
  Task::init(period);
  MsgService.init();
}

void WaterMonitor::tick() {
  routine();
}

void WaterMonitor::routine() {
  s->check();
  if (s->getData() > WL1) {
    normalState();
  } else if(s->getData() > WL2 && s->getData() <= WL1) {
    preAlarmState();
  } else {
    alarmState();
  }
}

void WaterMonitor::normalState() {
  if (state != NORMAL) {
    this->init(PE_NORMAL);
    state = NORMAL;
    MsgService.sendMsg(stateName[state]);
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
    MsgService.sendMsg(stateName[state]);
    manualMode = false;
    ledB->switchOn();
    m->setValveDegrees(MIN_DEGREES);
    lcd->turnOn();
    lcd->clear(2);
    lcd->print(getSituationString(), 0);
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
    MsgService.sendMsg(stateName[state]);
    ledB->switchOff();
    ledC->switchOn();
    lcd->turnOn();
    lcd->print(getSituationString(), 0);
    strcpy(buffer, "Water level: ");
    lcd->print(buffer, 1);
    strcpy(buffer, "Valve degrees: ");
    lcd->print(buffer, 2);
  }
  lcd->print(getWaterLevel(s), 1, 13);
  manualModeManager();
  if (!manualMode && !remoteManualMode) {
    degrees = map(s->getData(), WLMAX, WL2, MAX_DEGREES, MIN_DEGREES);
    //m->setValveDegrees(map(s->getData(), WLMAX, WL2, MAX_DEGREES, MIN_DEGREES));
  } else {
    if (manualMode) {
      degrees = map(pot->getValveDegrees(), 0, 1023, MAX_DEGREES, MIN_DEGREES);
    } else {
      degrees = atoi(degreesBuffer);
    }
  }
  m->setValveDegrees(degrees);
  lcd->print(getValveDegrees(m), 2, 15);
}

// This function sets the correct type of manual mode (remote or local) if necessary
void WaterMonitor::manualModeManager() {
  if (b->isPressed()) {
    manualMode = !manualMode;
    remoteManualMode = false;
    MsgService.sendMsg("RemoteControl-off");
  }
  if (remoteControl()) {
    switch(atoi(degreesBuffer)) {
      // Remote control on
      case -1:
        remoteManualMode = true;
        manualMode = false;
        strcpy(degreesBuffer, "0");
        break;
      // Remote control off
      case -2:
        remoteManualMode = false;
        strcpy(degreesBuffer, "0");
        break;
      default:
        break;
    }
  }
}

// Returns a string with the current situation
char* WaterMonitor::getSituationString() {
  strcpy(situation, "Situation: ");
  strcat(situation, stateName[state]);
  return situation;
}

void WaterMonitor::deactivationRoutine() {
  ledB->switchOff();
  ledC->switchOff();
  lcd->turnOff();
  m->setValveDegrees(MIN_DEGREES);
}

bool WaterMonitor::remoteControl() {
  if (MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();
    strcpy(degreesBuffer, msg->getContent().c_str());
    delete msg;
    return true;
  }
  return false;
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
char* getWaterLevel(Sensor* s) {
  char level[5];
  sprintf(level, "%d", MAX_WATER_LEVEL - s->getData());
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