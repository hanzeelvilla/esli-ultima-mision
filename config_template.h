// RENAME THIS FILE TO config.h

#ifndef CONFIG_H
#define CONFIG_H

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <MyLedIO.h>

#define SSID1 "your_ssid1"
#define PSWD1 "your_pswd1"
#define SSID2 "your_ssid2"
#define PSWD2 "your_pswd2"
// add more APs if needed
// #define SSID3 "your_ssid3"
// #define PSWD3 "your_pswd3"

#define WIFI_TIME_OUT 500
#define MAX_WIFI_CONNECT_TIME 30000

#define PROJECT_ENDPOINT "http:YOUR_SERVER_IP:3000/api/highscores/1" // change the port if necessary

#define WIFi_LED_PIN 15

#endif