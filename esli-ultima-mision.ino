#include "config.h"
#include "utils.h"

bool testEndpoint = false;

MyLedIO wifiLed(WIFi_LED_PIN);

JsonDocument doc;
String jsonPayload;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  configWifi();
  initWifi();

  wifiLed.init();

  doc["gamertag"] = "PICO";
  doc["points"] = 900;
  doc["shots"] = 90;
  doc["destroyedEnemies"] = 9;
  doc["destroyedBosses"] = 9;
  doc["gameTime"] = 900;
  serializeJson(doc, jsonPayload);
}

void loop() {
  if (wifiConnected()) {
    wifiLed.turnOn();
    
    if (!testEndpoint) {
      sendDataToAngelAPI(jsonPayload); // just once
      testEndpoint = true;
    }
      
  }
  else
    wifiLed.turnOff();

  delay(500);
}