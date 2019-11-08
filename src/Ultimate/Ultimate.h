#ifndef Ultimate_h
#define Ultimate_h

#include "../GPS.h"

class Ultimate : public GPS {
  public:
    Ultimate();
    virtual void setup() override;
    virtual void tick() override;
};

#endif
