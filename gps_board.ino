#include "src/GPS.h"
#include "src/Ultimate/Ultimate.h"

const int NUM_SENSORS = 1;
GPS* gps_array[1];

GPS* gps_factory(String type) {
  if(type == "ultimate") {
    return new Ultimate(&Serial, 9,10);
  }
  return nullptr;
}

void setup() {
  Serial.begin(9600);
  
  gps_array[0] = gps_factory("ultimate");

  for(int i = 0 ; i < NUM_SENSORS ; ++i) {
    gps_array[i]->setup();
  }
}


void loop() {
  for(int i = 0 ; i < NUM_SENSORS ; ++i) 
    gps_array[i]->tick();
}
