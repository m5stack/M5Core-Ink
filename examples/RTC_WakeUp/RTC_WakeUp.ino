#include "M5CoreInk.h"

void setup()
{
    M5.begin();
    digitalWrite(LED_EXT_PIN,LOW);
}

void loop()
{
    //Press PWR Btn for sleep , after 5 sec wakeup.
    if( M5.BtnPWR.wasPressed())
    {
        Serial.printf("Btn %d was pressed \r\n",BUTTON_EXT_PIN);
        M5.shutdown(5);
        //M5.shutdown(RTC_TimeTypeDef(10,2,0));
    }
    //M5.rtc.SetAlarmIRQ(RTC_TimeTypeDef(10,2,0));
    M5.update();
}