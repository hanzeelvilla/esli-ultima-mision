#include "config.h"
#include "utils.h"

bool testEndpoints = false;

MyLedIO wifiLed(WIFi_LED_PIN);

JsonDocument jsonProject;
String jsonProjectPayload;

JsonDocument jsonConcurso;
String jsonConcursoPayload;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  configWifi();
  initWifi();

  wifiLed.init();

  // Our API
  jsonProject["gamertag"] = "PICO";
  jsonProject["points"] = 900;
  jsonProject["shots"] = 90;
  jsonProject["destroyedEnemies"] = 9;
  jsonProject["destroyedBosses"] = 9;
  jsonProject["gameTime"] = 900;
  serializeJson(jsonProject, jsonProjectPayload);
}

void loop() {
  if (wifiConnected()) {
    wifiLed.turnOn();
    
    if (!testEndpoints) {
      // just once
      sendDataToAngelAPI(jsonProjectPayload);
      sendDataToConcursoAPI(3, 3, 3);
      testEndpoints = true;
    }
      
  }
  else
    wifiLed.turnOff();

  delay(500);
}