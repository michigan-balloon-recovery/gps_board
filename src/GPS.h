#ifndef GPS_h
#define GPS_h

#include "Arduino.h"

class GPS {
  public:
    virtual void setup() = 0;
    virtual void tick() = 0;
};

#endif
