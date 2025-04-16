#include "config.h"
#include "utils.h"

MyLedIO wifiLed(WIFi_LED_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  configWifi();
  initWifi();

  wifiLed.init();
}

void loop() {
  if (wifiConnected())
    wifiLed.turnOn();
  else
    wifiLed.turnOff();

  delay(500);
}