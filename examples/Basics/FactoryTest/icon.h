#ifndef _ICON_H_
#define _ICON_H_

#include "utility/Ink_Sprite.h"

extern unsigned char image_CoreInkWelcome[5000];
extern unsigned char image_CoreInkTime[5000];
extern unsigned char image_CoreInkWifi[5000];
extern unsigned char image_CoreInkWWellcome[5000];
extern unsigned char image_coreInkMain[5000];

typedef enum {
    kRGBImage,
} ImangePixMode_t;

typedef struct {
    int width;
    int height;
    int bitCount;
    unsigned char *ptr;
} image_t;

// Num40x55
extern unsigned char image_num_01[275];  //"0"  W:40 H:55
extern unsigned char image_num_02[275];  //"1"  W:40 H:55
extern unsigned char image_num_03[275];  //"2"  W:40 H:55
extern unsigned char image_num_04[275];  //"3"  W:40 H:55
extern unsigned char image_num_05[275];  //"4"  W:40 H:55
extern unsigned char image_num_06[275];  //"5"  W:40 H:55
extern unsigned char image_num_07[275];  //"6"  W:40 H:55
extern unsigned char image_num_08[275];  //"7"  W:40 H:55
extern unsigned char image_num_09[275];  //"8"  W:40 H:55
extern unsigned char image_num_10[275];  //"9"  W:40 H:55
extern unsigned char image_num_11[165];  //":"  W:24 H:55

// Num18x29
extern unsigned char image_num_29_01[66];  //"0"  W:18 H:29
extern unsigned char image_num_29_02[66];  //"1"  W:18 H:29
extern unsigned char image_num_29_03[66];  //"2"  W:18 H:29
extern unsigned char image_num_29_04[66];  //"3"  W:18 H:29
extern unsigned char image_num_29_05[66];  //"4"  W:18 H:29
extern unsigned char image_num_29_06[66];  //"5"  W:18 H:29
extern unsigned char image_num_29_07[66];  //"6"  W:18 H:29
extern unsigned char image_num_29_08[66];  //"7"  W:18 H:29
extern unsigned char image_num_29_09[66];  //"8"  W:18 H:29
extern unsigned char image_num_29_10[66];  //"9"  W:18 H:29
extern unsigned char image_num_29_11[66];  //"/"  W:18 H:29

extern image_t warningImage;
extern image_t wifiScanImage;

extern image_t num55[11];
extern image_t num18x29[11];

#endif