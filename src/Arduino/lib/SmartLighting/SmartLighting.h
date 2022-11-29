#ifndef __SMARTLIGHTING__
#define __SMARTLIGHTING__

#include "Task.h"
#include "Led.h"
#include "Pir.h"
#include "Sensor.h"
#include "MsgService.h"

class SmartLighting : public Task {
public:
  SmartLighting();
  void init(int period);
  void tick();

private:
  Led* ledA;
  Pir* p;
  Sensor* ls;
  void routine();
  void deactivationRoutine();

};

#endif