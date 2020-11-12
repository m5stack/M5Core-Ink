#include "M5CoreInk.h"

M5CoreInk::M5CoreInk(/* args */)
{
}

M5CoreInk::~M5CoreInk()
{
}

int M5CoreInk::begin(bool InkEnable, bool wireEnable, bool SpeakerEnable)
{
    pinMode(POWER_HOLD_PIN, OUTPUT);
    digitalWrite(POWER_HOLD_PIN, HIGH); // Hold power

    pinMode(LED_EXT_PIN, OUTPUT);

    Serial.begin(115200);
    Serial.printf("initializing.....OK\n");

    if (wireEnable)
    {
        Wire.begin(32, 33, 10000);
    }

    if (SpeakerEnable)
    {
        Speaker.begin();
    }

    rtc.begin();

    if (InkEnable)
    {
        M5Ink.begin();
        if (!M5.M5Ink.isInit())
        {
            Serial.printf("Ink initializ is faild\n");
            return -1;
        }
    }

    return 0;
}

void M5CoreInk::update()
{
    BtnUP.read();
    BtnDOWN.read();
    BtnMID.read();
    BtnEXT.read();
    BtnPWR.read();

    Speaker.update();
}

void M5CoreInk::shutdown()
{
    M5Ink.deepSleep();
    digitalWrite(POWER_HOLD_PIN, LOW);
}
int M5CoreInk::shutdown(int seconds)
{
    M5Ink.deepSleep();
    rtc.SetAlarmIRQ(seconds);
    digitalWrite(POWER_HOLD_PIN, LOW);
}
int M5CoreInk::shutdown(const RTC_TimeTypeDef &RTC_TimeStruct)
{
    M5Ink.deepSleep();
    rtc.SetAlarmIRQ(RTC_TimeStruct);
    digitalWrite(POWER_HOLD_PIN, LOW);
}
int M5CoreInk::shutdown(const RTC_DateTypeDef &RTC_DateStruct, const RTC_TimeTypeDef &RTC_TimeStruct)
{
    M5Ink.deepSleep();
    rtc.SetAlarmIRQ(RTC_DateStruct,RTC_TimeStruct);
    digitalWrite(POWER_HOLD_PIN, LOW);
}

M5CoreInk M5;