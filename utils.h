#ifndef UTILS_H
#define UTILS_H

#include "config.h"

WiFiMulti wifiMulti;
HTTPClient http;
WiFiClientSecure secureClient; 

bool wifiConnected();
void configWifi();
void initWifi();
void sendDataToAngelAPI(const String& requestBody);
void sendDataToConcursoAPI(int disparos, int enemigosDestruidos, unsigned long tiempoJuego); 

// WIFI
bool wifiConnected() {
  return wifiMulti.run() == WL_CONNECTED;
}

void configWifi() {
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(SSID1, PSWD1);
  wifiMulti.addAP(SSID2, PSWD2); // comment or remove this line if you only have one AP
  // add more APs if needed

  secureClient.setInsecure();
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

void sendDataToAngelAPI(const String& requestBody) {
  if (wifiConnected()) {

    http.begin(PROJECT_ENDPOINT);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-api-key", API_KEY);

    Serial.println("Updating Highscore - Fetching Angel's API");
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

      if (httpResponseCode == -1) {
        Serial.println("Check the URL or server connection.");
      }
    }
    
    http.end();
  }
  else
    Serial.println("Failed to connect to WiFi.");
}

void sendDataToConcursoAPI(int disparos, int enemigosDestruidos, unsigned long tiempoJuego) {
  if (wifiConnected()) {
    http.begin(secureClient, CONCURSO_ENDPOINT);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String post_data = "device_name=" + String(DEVICE_NAME) + 
                      "&disparos=" + String(disparos) + 
                      "&enemigos_destruidos=" + String(enemigosDestruidos) + 
                      "&tiempo_juego=" + String(tiempoJuego);

    Serial.println("Uploading new Highscore - Fetching Concurso API");
    int httpResponseCode = http.POST(post_data);

    if (httpResponseCode > 0) {
      String response = http.getString();

      Serial.print("Status Code: ");
      Serial.println(httpResponseCode);
      Serial.print("Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error: ");
      Serial.println(httpResponseCode);

      if (httpResponseCode == -1) {
        Serial.println("Check the URL or server connection.");
      }
    }
    
    http.end();
  }
  else
    Serial.println("Failed to connect to WiFi.");
}

#endif