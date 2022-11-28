#ifndef __SMARTLIGHTING__
#define __SMARTLIGHTING__

#include "Task.h"
#include "Led.h"
#include "Pir.h"
#include "LightSensor.h"
#include "MsgService.h"

class SmartLighting : public Task {
public:
  SmartLighting();
  void init(int period);
  void tick();
  void activate();
  void deactivate();

private:
  Led* ledA;
  Pir* p;
  LightSensor* ls;
  MsgServiceClass* msgService;
  bool active;
  void routine();
};

#endif