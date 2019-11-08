#include "Arduino.h"
#include "Ultimate.h"

Ultimate::Ultimate() {
}

void Ultimate::setup(){
  Serial.println("Setup called!");
}
void Ultimate::tick() {
  Serial.println("Tick invoked!");
}
