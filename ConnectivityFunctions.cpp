#include "ConnectivityFunctions.h"

String connectToWiFi(const char* ssid, const char* password) {
  // Connect to WiFi
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 400) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    return "Connected to WiFi network!";
  } else {
    return "Failed to connect to WiFi. Check your credentials or network.";
  }
}

void sendHttpRequest(HTTPClient& http, const char* url) {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode == 200) {
      Serial.println("HTTP request success");
    } else {
      Serial.println("HTTP request failed");
      Serial.println(httpCode);
    }
  } else {
    Serial.println("WiFi not connected");
  }
}
