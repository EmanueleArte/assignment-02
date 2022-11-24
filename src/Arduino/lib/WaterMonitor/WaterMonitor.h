#ifndef __WATERMONITOR__
#define __WATERMONITOR__

#include "Task.h"
#include "Led.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "Sonar.h"
#include "Button.h"
#include "Lcd.h"
#include "MsgService.h"

#define WL1 40
#define WL2 20
#define WLMAX 0
#define PE_NORMAL 500
#define PE_PRE_ALARM 200
#define PE_ALARM 100

class WaterMonitor : public Task {
public:
  WaterMonitor();  
  void init(int period);  
  void tick();

private:
  Led* ledB;
  Led* ledC;
  Motor* m;
  Potentiometer* pot;
  Sonar* s;
  Button* b;
  Lcd* lcd;
  MsgServiceClass* msgService;
  void routine();
  void normalState();
  void preAlarmState();
  void alarmState();
};

#endif