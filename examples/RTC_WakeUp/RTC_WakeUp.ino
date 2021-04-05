#include "M5CoreInk.h"

Ink_Sprite InkPageSprite(&M5.M5Ink);

void setup()
{
    M5.begin();
    digitalWrite(LED_EXT_PIN,LOW);
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
    InkPageSprite.drawString(10,50,"Press EXT Btn for sleep");
    InkPageSprite.drawString(15,80,"after 30 sec wakeup.");
    InkPageSprite.drawString(10,110,"Press PWR Btn for");
    InkPageSprite.drawString(15,140,"shutdown.");
    InkPageSprite.pushSprite();
}

void loop()
{
    //Press EXT Btn for sleep , after 30 sec wakeup.
    if( M5.BtnEXT.wasPressed())
    {
        Serial.printf("Btn %d was pressed \r\n",BUTTON_EXT_PIN);
        M5.M5Ink.deepSleepEink(); // Eink wakeup through setup routine
        M5.deepSleepESP(30);
    }
    //Press PWR Btn for shutdown
    if( M5.BtnPWR.wasPressed())
    {
        Serial.printf("Btn %d was pressed \r\n",BUTTON_PWR_PIN);
        M5.shutdown();
    }
    M5.update();
}
