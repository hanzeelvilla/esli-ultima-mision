#ifndef UTILS_H
#define UTILS_H

#include "config.h"

WiFiMulti wifiMulti;

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
  
}

#endif