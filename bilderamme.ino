#include <Arduino.h>
#include "setup.h"
#include "ConnectivityFunctions.h"
#include "JsonParsingFunctions.h"

// WiFi credentials
extern const char* ssid = "E42";
extern const char* password = "Tildeerkul";

const int pixel_width = 639;
const int pixel_height = 350;

void setup() {
  Serial.begin(115200);
}


void loop() {
  init_screen();
  Serial.println(connectToWiFi(ssid, password));
  
  // yr.no API
  HTTPClient httpYr;
  sendHttpRequest(httpYr, "https://www.yr.no/api/v0/locations/1-2376/forecast");
  float* resultYr = parseJsonResponseForYr(httpYr);
  for (int i = 0; i < 10; i++) {
    Serial.println(resultYr[i]);
  }

  // Example usage with another URL
  HTTPClient httpSnow;
  sendHttpRequest(httpSnow, "https://www.yr.no/api/v0/observations/snowdepths/regions/NO-42?language=nb");
  char** resultSnow = parseJsonResponseForSnow(httpSnow);
  char** locations = new char*[3];
  locations[0] = strdup("Kr.sand:");
  locations[1] = strdup("Bortelid:");
  locations[2] = strdup("Hovden:");

  #if 1  
  //1.Select Image
  printf("SelectImage:BlackImage\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  int x = 50; int y = 310;
  Paint_DrawRectangle(x, y, x+170, y+60, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
  for (int i = 0; i < 3; i++) {
    Paint_DrawString_EN(x+3, y+5+(i*17), locations[i], &Font16, WHITE, BLACK);
    Paint_DrawString_EN(x+100, y+3+(i*17), resultSnow[i], &Font20, WHITE, BLACK);
  }
  

  EPD_7IN5_Display(BlackImage);
  DEV_Delay_ms(2000);

  #endif

  printf("Goto Sleep...\r\n");
  EPD_7IN5BC_Sleep();
  free(BlackImage);
  free(RYImage);
  BlackImage = NULL;
  RYImage = NULL;

  delay(500000); 
}
