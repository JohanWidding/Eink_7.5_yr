#ifndef CONNECTIVITY_FUNCTIONS_H
#define CONNECTIVITY_FUNCTIONS_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

String connectToWiFi(const char* ssid, const char* password);
void sendHttpRequest(HTTPClient& http, const char* url);


#endif  // CONNECTIVITY_FUNCTIONS_H
