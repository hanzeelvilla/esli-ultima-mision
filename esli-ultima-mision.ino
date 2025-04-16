#include "config.h"
#include "utils.h"

bool testEndpoint = false;

MyLedIO wifiLed(WIFi_LED_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  configWifi();
  initWifi();

  wifiLed.init();
}

void loop() {
  if (wifiConnected()) {
    wifiLed.turnOn();
    
    if (!testEndpoint) {
      sendDataToAngelAPI(); // just once
      testEndpoint = true;
    }
      
  }
  else
    wifiLed.turnOff();

  delay(500);
}