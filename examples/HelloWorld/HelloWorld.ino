#include "M5CoreInk.h"

Ink_Sprite InkPageSprite(&M5.M5Ink);

void setup() {

    M5.begin();
    if( !M5.M5Ink.isInit())
    {
        Serial.printf("Ink Init faild");
        while (1) delay(100);   
    }
    M5.M5Ink.clear();
    delay(1000);
    //creat ink refresh Sprite
    if( InkPageSprite.creatSprite(0,0,200,200,true) != 0 )
    {
        Serial.printf("Ink Sprite creat faild");
    }
    InkPageSprite.drawString(35,50,"Hello World!");
    InkPageSprite.pushSprite();
}

void loop() {

}