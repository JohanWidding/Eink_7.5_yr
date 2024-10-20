#ifndef JSON_PARSING_FUNCTIONS_H
#define JSON_PARSING_FUNCTIONS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

float* parseJsonResponseForYr(HTTPClient& http);
char** parseJsonResponseForSnow(HTTPClient& http);

#endif  // JSON_PARSING_FUNCTIONS_H
