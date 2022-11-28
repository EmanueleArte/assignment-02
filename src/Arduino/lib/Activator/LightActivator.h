#ifndef __LIGHT_ACTIVATOR__
#define __LIGHT_ACTIVATOR__

#include "Task.h"

class LightActivator : public Task {
  Task* SmartLighting;
  Task* WaterMonitor;
  int activationPeriod;

public:
  // task1 is the task to be activated, task2 is the task that activates task1
  LightActivator(Task* t1, Task* t2, int period) {
    SmartLighting = t1;
    WaterMonitor = t2;
    activationPeriod = period;
  }
  
  void init(int period) {
    Task::init(period);
  }

  void tick() {
    manageTask();
  }

private:  
  void manageTask() {
    if (WaterMonitor->getPeriod() == activationPeriod) {
      SmartLighting->setActive(false);
    } else {
      SmartLighting->setActive(true);
    }
  }

};

#endif