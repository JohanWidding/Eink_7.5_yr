// setup.cpp
#include "setup.h"

UBYTE *BlackImage = nullptr;
UBYTE *RYImage = nullptr;

void init_screen() {

    DEV_Module_Init();
    printf("e-Paper Init and Clear...\r\n");
    EPD_7IN5BC_Init();
    EPD_7IN5BC_Clear();
    DEV_Delay_ms(500);

    //Create a new image cache named IMAGE_BW and fill it with white
    UWORD Imagesize = ((EPD_7IN5BC_WIDTH % 8 == 0) ? (EPD_7IN5BC_WIDTH / 8 ) : (EPD_7IN5BC_WIDTH / 8)) * EPD_7IN5BC_HEIGHT;
    if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
      printf("Failed to apply for black memory...\r\n");
      while(1);
    }
    if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
      printf("Failed to apply for red memory...\r\n");
      while(1);
    }
    printf("NewImage:BlackImage and RYImage\r\n");
    Paint_NewImage(BlackImage, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, 0, WHITE);
    Paint_NewImage(RYImage, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, 0, WHITE);
}