#ifndef UTILS_H
#define UTILS_H

#include "config.h"

WiFiMulti wifiMulti;
HTTPClient http;

bool wifiConnected();
void configWifi();
void initWifi();
void sendDataToAngelAPI();
void sendDataToConcursoAPI(); 

// WIFI
bool wifiConnected() {
  return wifiMulti.run() == WL_CONNECTED;
}

void configWifi() {
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(SSID1, PSWD1);
  wifiMulti.addAP(SSID2, PSWD2); // comment or remove this line if you only have one AP
  // add more APs if needed
}

void initWifi() {
  Serial.println("Connecting to WiFi...");
  unsigned long currentTime = 0;
  unsigned long previousTime = 0;
  unsigned long startAttemptTime = millis();
  
  while (!wifiConnected()) {
    currentTime = millis();
    if (currentTime - previousTime >= WIFI_TIME_OUT) {
      previousTime = currentTime;
      Serial.print(".");
    }
    if (millis() - startAttemptTime >= MAX_WIFI_CONNECT_TIME) {
      Serial.println("\nFailed to connect to WiFi.");
      Serial.println("The game will continue without Internet connection.");
      return;
    }
    delay(100);
  }
  
  Serial.println("\nWiFi connected");
  Serial.println("SSID: " + WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendDataToAngelAPI() {
  if (wifiConnected()) {

    http.begin(PROJECT_ENDPOINT);
    http.addHeader("Content-Type", "application/json");

    JsonDocument doc;
    doc["gamertag"] = "PICO";
    doc["points"] = 9999;
    doc["shots"] = 9999;
    doc["destroyedEnemies"] = 9999;
    doc["destroyedBosses"] = 9999;
    doc["gameTime"] = 9999;

    String requestBody;
    serializeJson(doc, requestBody);

    Serial.println("Updating Highscore");
    int httpResponseCode = http.PUT(requestBody);

    if (httpResponseCode > 0) {
      String response = http.getString();

      Serial.print("Status Code: ");
      Serial.println(httpResponseCode);
      Serial.print("Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
  else
    Serial.println("Failed to connect to WiFi.");
}

#endif