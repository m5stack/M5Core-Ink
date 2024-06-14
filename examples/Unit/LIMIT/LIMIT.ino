/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5CoreInk sample source code
*                          配套  M5CoreInk 示例源代码
* Visit the website for more information:
* 获取更多资料请访问:
*
* Product:  Limit.
* Date: 2022/6/1
*******************************************************************************
*/

#include <M5CoreInk.h>

Ink_Sprite InkPageSprite(&M5.M5Ink);

#define KEY_PIN 33  // Define Limit Pin.  定义Limit连接引脚

void setup() {
    M5.begin();         // Init M5Stack  初始化M5Stack
    M5.M5Ink.isInit();  // Init E-INK screen.  初始化E-INK屏幕驱动
    M5.M5Ink.clear();
    delay(1000);
    if (InkPageSprite.creatSprite(0, 0, 200, 200, true) !=
        0) {  // creat ink refresh Sprite.  创建画布.
        Serial.printf("Ink Sprite creat faild");
    } else {
        Serial.printf("creatSprite success\n");
    }
    InkPageSprite.drawString(30, 50, "UNIT-LIMIT Example");
    InkPageSprite.drawString(8, 70, "Beep when limit was hit");
    InkPageSprite.pushSprite();

    pinMode(KEY_PIN, INPUT_PULLUP);  // Init Limit pin.  初始化Limit引脚.
}

void loop() {
    if (!digitalRead(KEY_PIN)) {  // If Limit was hit.  如果触碰了Limit.
        M5.Speaker.beep();
    } else {
        M5.Speaker.mute();
    }
    delay(100);
}
