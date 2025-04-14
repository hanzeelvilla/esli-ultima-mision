#include "config.h"
#include "utils.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  configWifi();
  initWifi();
}

void loop() {
  
}