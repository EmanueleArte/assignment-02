#ifndef __WATERMONITOR__
#define __WATERMONITOR__

#include "Task.h"
#include "Led.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "Sensor.h"
#include "Button.h"
#include "Lcd.h"
#include "MsgService.h"

#define WL1 40
#define WL2 20
#define WLMAX 0
#define PE_NORMAL 2000
#define PE_PRE_ALARM 1000
#define PE_ALARM 500

enum State { NORMAL, PRE_ALARM, ALARM, NONE };

class WaterMonitor : public Task {
public:
  WaterMonitor(Sensor* s);
  void init(int period);
  void tick();

private:
  Led* ledB;
  Led* ledC;
  Motor* m;
  Potentiometer* pot;
  Sensor* s;
  Button* b;
  Lcd* lcd;
  State state;
  bool manualMode;
  bool remoteManualMode;
  void routine();
  void normalState();
  void preAlarmState();
  void alarmState();
  char* getSituationString();
  void deactivationRoutine();
  void manualModeManager();
  bool remoteControl();

};

#endif