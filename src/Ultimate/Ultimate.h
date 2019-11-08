#ifndef Ultimate_h
#define Ultimate_h

#include <SoftwareSerial.h>
#include "../GPS.h"

class Ultimate : public GPS {
  public:
    Ultimate(Stream* logger, int rx, int tx);
    static const int GPS_DATA_BUFFER_SIZE = 256;
    virtual void setup() override;
    virtual void tick() override;
  private:
    int rx, tx;
    SoftwareSerial sensor; // RX, TX
    char GPSDataBuffer[GPS_DATA_BUFFER_SIZE] = {0x00};
    uint8_t GPSDataBufferIndex = 0;
    void resetGPSDataBufferAndIndex();
    bool scanGPSDataBufferForGPGGA(uint8_t *offset, uint8_t *len); 


};

#endif
