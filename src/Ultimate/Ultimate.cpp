#include "Arduino.h"
#include "Ultimate.h"

Ultimate::Ultimate(Stream* logger, int rx, int tx) : GPS::GPS(logger), rx(rx), tx(tx), sensor(rx, tx) {
}

void Ultimate::setup(){
  //Serial.println("Setup called!");
  sensor.begin(9600);
  sensor.listen();

}


/*
 * Sets every value in the buffer to \0 and resets the buffer index to 0
 */
void Ultimate::resetGPSDataBufferAndIndex() {
  for(int i = 0 ; i < GPS_DATA_BUFFER_SIZE - 1 ; i++) { 
    if(GPSDataBuffer[i] == '\0') break;
    GPSDataBuffer[i] = '\0'; 
  }
  GPSDataBufferIndex = 0;
}

/*
 * Scans the GPSDataBuffer for a $GPGGA string and sets the offset pointer to the location of the $, and len for the number of characters til '\n'
 * Note: The parameters of this function are outputs
 * 
 * @returns true if the string was found, false if not
 */
bool Ultimate::scanGPSDataBufferForGPGGA(uint8_t *offset, uint8_t *len) { 
  char *GPGGAPtr = strstr(GPSDataBuffer, "$GPGGA,"); // First occurance of "$GPGGA," in the buffer

  if(GPGGAPtr) {
    char *newLinePtr = strchr(GPGGAPtr, '\n'); // First occurance of \n in the buffer
    
    if(newLinePtr) {   
      *offset = GPGGAPtr - GPSDataBuffer; 
      *len = newLinePtr - GPGGAPtr; 

      return true;
    }
  }

  // If either pointer is null, it means we hit a \0 before finding what we wanted
  return false;
}

void Ultimate::tick() {
  //Serial.println("Tick invoked!");
  // BEGIN RX ONLY
  sensor.begin(9600);
  sensor.listen();

  // This loop will hang for enough time to fill our GPS buffer
  //    We assume that the buffer can be read at ~1 Hz
  long startTime = millis();  
  while( (millis() < startTime + GPS_DATA_BUFFER_SIZE + 2) && (GPSDataBufferIndex != GPS_DATA_BUFFER_SIZE - 1)) 
    if(sensor.available())
      GPSDataBuffer[GPSDataBufferIndex++] = sensor.read();
 
  sensor.end();
  // END RX ONLY

  // BEGIN TX ONLY
  uint8_t *offset;
  uint8_t *len;
  if(scanGPSDataBufferForGPGGA(offset, len)) 
    for(int i = *offset ; i <= *len; i++)  
      Serial.write(GPSDataBuffer[i]);
  // END TX ONLY
  
  resetGPSDataBufferAndIndex();  
}
