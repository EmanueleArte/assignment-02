#ifndef __DATA_SENDER__
#define __DATA_SENDER__

#include "Task.h"
#include "MsgService.h"
#include "Sensor.h"

class DataSender : public Task {

public:
  DataSender(Sensor* s);
  void init(int period);
  void tick();

private:
  Sensor* sensor;
  void sendData();
  void deactivationRoutine();

};

#endif