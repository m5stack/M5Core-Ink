#include "M5CoreInk.h"
#include "driver/gpio.h"

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
	gpio_hold_en((gpio_num_t)POWER_HOLD_PIN); // Hold power during deepSleep
	
    pinMode(LED_EXT_PIN, OUTPUT);

    Serial.begin(115200);
    Serial.printf("initializing github library OK\n");

    if (wireEnable)
    {
        Wire.begin(32, 33, 10000);
    }

    if (SpeakerEnable)
    {
        Speaker.begin();
    }

    rtc.begin();
    rtc.clearIRQ();

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
	// Disable power to shutdown device
	gpio_hold_dis((gpio_num_t)POWER_HOLD_PIN);
    digitalWrite(POWER_HOLD_PIN, LOW);
}
int M5CoreInk::deepSleepESP(int seconds)
{
    rtc.clearIRQ();
    rtc.SetAlarmIRQ(seconds);
    delay(10);
	esp_deep_sleep_start();
    return 0;
}
int M5CoreInk::shutdown(const RTC_TimeTypeDef &RTC_TimeStruct)
{
    rtc.clearIRQ();
    rtc.SetAlarmIRQ(RTC_TimeStruct);
    delay(10);
	esp_deep_sleep_start();
    return 0;
}
int M5CoreInk::shutdown(const RTC_DateTypeDef &RTC_DateStruct, const RTC_TimeTypeDef &RTC_TimeStruct)
{
    rtc.clearIRQ();
    rtc.SetAlarmIRQ(RTC_DateStruct,RTC_TimeStruct);
    delay(10);
	esp_deep_sleep_start();
    return 0;
}

M5CoreInk M5;