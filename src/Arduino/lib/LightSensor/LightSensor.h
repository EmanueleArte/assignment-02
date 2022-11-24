#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

class LightSensor {
public:
  // aggiungere interfaccia comune
  LightSensor(int pin, int threshold);
  bool check();

private:
  int pin;
  int threshold;
};

#endif