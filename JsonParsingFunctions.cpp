#include "JsonParsingFunctions.h"
#include "getValue_function.h"

float* parseJsonResponseForYr(HTTPClient& http) {
  String payload = extractDataByKey(http, "temperature", ",", 24);
  http.end();
  Serial.println(payload);

  float* temperatures = new float[10]; // Declare a vector to store temperature values

  // Your existing JSON parsing logic here
  // For example, assuming payload is a JSON string
  DynamicJsonDocument doc(1000);
  deserializeJson(doc, payload);

  for (int i = 0; i < 10; i++) {
    Serial.println(static_cast<float>(doc[i]));
    // Convert the temperature value to an integer and add it to the vector
    temperatures[i] = doc[i];
  }

  // Clear the payload after use
  payload = "";

  return temperatures; // Return the vector containing temperature values
}

char** parseJsonResponseForSnow(HTTPClient& http) {
  String payload = extractDataByKey(http, "snow\"", "}", 2);
  http.end();
  Serial.println(payload);

  // Your existing JSON parsing logic here
  // For example, assuming payload is a JSON string
  DynamicJsonDocument doc(1000);
  deserializeJson(doc, payload);

  int snowLjosland = static_cast<int>(doc[3]["depth"]);
  int snowHovden = static_cast<int>(doc[6]["depth"]);
  int snowKristiansand = static_cast<int>(doc[13]["depth"]);

  // Convert int values to strings
  char strSnowLjosland[10];
  char strSnowHovden[10];
  char strSnowKristiansand[10];

  itoa(snowLjosland, strSnowLjosland, 10);
  itoa(snowHovden, strSnowHovden, 10);
  itoa(snowKristiansand, strSnowKristiansand, 10);

  // Create an array of char arrays
  char** snowValues = new char*[3];
  snowValues[0] = strdup(strcat(strSnowKristiansand, "cm"));
  snowValues[1] = strdup(strcat(strSnowLjosland, "cm"));
  snowValues[2] = strdup(strcat(strSnowHovden, "cm"));

  // Clear the payload after use
  payload = "";

  return snowValues;
}


