#include "M5CoreInk.h"

Ink_Sprite InkPageSprite(&M5.M5Ink);

void ButtonTest(char* str)
{
    InkPageSprite.clear();
    InkPageSprite.drawString(35,59,str);
    InkPageSprite.pushSprite();
    delay(2000);
}

void setup() {

    M5.begin();
    if( !M5.M5Ink.isInit())
    {
        Serial.printf("Ink Init faild");
    }
    M5.M5Ink.clear();
    delay(1000);
    //creat ink refresh Sprite
    if( InkPageSprite.creatSprite(0,0,200,200,true) != 0 )
    {
        Serial.printf("Ink Sprite creat faild");
    }
}

void loop() {
    if( M5.BtnUP.wasPressed()) ButtonTest("Btn UP Pressed");
    if( M5.BtnDOWN.wasPressed()) ButtonTest("Btn DOWN Pressed");
    if( M5.BtnMID.wasPressed()) ButtonTest("Btn MID Pressed");
    if( M5.BtnEXT.wasPressed()) ButtonTest("Btn EXT Pressed");
    if( M5.BtnPWR.wasPressed()){
        ButtonTest("Btn PWR Pressed");
        M5.PowerDown();
    }
    M5.update();
}