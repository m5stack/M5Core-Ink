#include "M5CoreInk.h"

Ink_Sprite InkPageSprite(&M5.M5Ink);

void setup()
{
    M5.begin();
    digitalWrite(LED_EXT_PIN,LOW);
    if( !M5.M5Ink.isInit())
    {
        Serial.printf("Ink Init failed");
        while (1) delay(100);   
    }
    M5.M5Ink.clear();
    delay(1000);
    //creat ink refresh Sprite
    if( InkPageSprite.creatSprite(0,0,200,200,true) != 0 )
    {
        Serial.printf("Ink Sprite create failed");
    }
    InkPageSprite.drawString(10,50,"Press PWR Btn for sleep");
    InkPageSprite.drawString(15,80,"after 5 sec wakeup.");
    InkPageSprite.pushSprite();
}

void loop()
{
    //Press PWR Btn for sleep , after 5 sec wakeup.
    if( M5.BtnPWR.wasPressed())
    {
        Serial.printf("Btn %d was pressed \r\n",BUTTON_PWR_PIN);
        M5.shutdown(5);
        //M5.shutdown(RTC_TimeTypeDef(10,2,0));
    }
    //M5.rtc.SetAlarmIRQ(RTC_TimeTypeDef(10,2,0));
    M5.update();
}
