#ifndef __SENSOR__
#define __SENSOR__

class Sensor {

public:
  virtual bool check() = 0;
  virtual int getData() = 0;

};

#endif