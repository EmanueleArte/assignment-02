#include "DataSender.h"

DataSender::DataSender(Sensor* s) {
  sensor = s;
}

void DataSender::init(int period) {
  Task::init(period);
}

void DataSender::tick() {
  sendData();
}

void DataSender::sendData() {
  char* msg = new char[10];
  sprintf(msg, "%d", sensor->getData());
  MsgService.sendMsg(msg);
}

void DataSender::deactivationRoutine() {
  // Nothing to do
}