#include "config.h"
#include "utils.h"

bool testEndpoint = false;

MyLedIO wifiLed(WIFi_LED_PIN);

JsonDocument doc;
String jsonPayload;
#define TEST_RANK 1

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  configWifi();
  initWifi();

  wifiLed.init();

  doc["gamertag"] = "PICO";
  doc["points"] = 9999;
  doc["shots"] = 9999;
  doc["destroyedEnemies"] = 9999;
  doc["destroyedBosses"] = 9999;
  doc["gameTime"] = 9999;
  serializeJson(doc, jsonPayload);
}

void loop() {
  if (wifiConnected()) {
    wifiLed.turnOn();
    
    if (!testEndpoint) {
      sendDataToAngelAPI(jsonPayload, TEST_RANK); // just once
      testEndpoint = true;
    }
      
  }
  else
    wifiLed.turnOff();

  delay(500);
}