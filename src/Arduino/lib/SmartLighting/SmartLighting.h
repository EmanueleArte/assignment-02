#ifndef __SMARTLIGHTING__
#define __SMARTLIGHTING__

#include "Task.h"
#include "Led.h"
#include "Pir.h"
#include "LightSensor.h"

class SmartLighting : public Task {
public:
  SmartLighting();  
  void init(int period);  
  void tick();

private:
  Led* ledA;
  Pir* p;
  LightSensor* ls;
  void routine();
};

#endif