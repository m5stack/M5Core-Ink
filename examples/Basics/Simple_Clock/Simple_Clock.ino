/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with CoreInk sample source code
*                          配套  CoreInk 示例源代码
* Visit for more information：https://docs.m5stack.com/en/core/coreink
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/coreink
*
* Describe: Simple Clock.  简易时钟
* Date: 2022/8/30
*******************************************************************************
  A simple clock based on M5CoreInk.
  Libraries:
  - [M5Unified](https://github.com/m5stack/M5Unified)
  - [M5GFX](https://github.com/m5stack/M5GFX)
*/

#include <WiFi.h>
#include <sntp.h>
#include <M5Unified.h>

#define WIFI_SSID     "YOUR WIFI SSID"
#define WIFI_PASSWORD "YOUR WIFI PASSWD"
#define NTP_TIMEZONE  "JST-8"
#define NTP_SERVER1   "ntp.aliyun.com"
#define NTP_SERVER2   "ntp1.aliyun.com"
#define NTP_SERVER3   "ntp2.aliyun.com"

void setup(void) {
    auto cfg = M5.config();

    cfg.external_rtc  = true;
    cfg.clear_display = false;

    M5.begin(cfg);

    if (!M5.Rtc.getIRQstatus()) {
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        configTzTime(NTP_TIMEZONE, NTP_SERVER1, NTP_SERVER2, NTP_SERVER3);

        while (WiFi.status() != WL_CONNECTED) {
            Serial.print('.');
            delay(500);
        }
        Serial.println("\r\n WiFi Connected.");

        while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED) {
            Serial.print('.');
            delay(500);
        }
        Serial.println("\r\n NTP Connected.");

        time_t t = time(nullptr) + 1;
        while (t > time(nullptr))
            ;

        M5.Rtc.setDateTime(localtime(&t));
    }

    auto dt = M5.Rtc.getDateTime();

    while (dt.time.seconds != 0) {
        dt = M5.Rtc.getDateTime();
        delay(500);
    }

    M5.Display.setFreeFont(&Orbitron_Light_24);
    if (dt.time.minutes == 30) {
        M5.Display.clear(TFT_WHITE);
        M5.Display.setTextSize(2.5);
        M5.Display.drawCenterString("Clock", 100, 120);
    }

    char buf[32] = {0};
    M5.Display.setTextSize(2);
    M5.Display.fillRect(0, 0, 200, 100);
    sprintf(buf, "%02d:%02d", dt.time.hours, dt.time.minutes);
    M5.Display.drawCenterString(buf, 100, 10);
    M5.Display.setTextSize(1);
    sprintf(buf, "%02d-%02d-%04d", dt.date.date, dt.date.month, dt.date.year);
    M5.Display.drawCenterString(buf, 100, 70);

    M5.Display.sleep();
    M5.Rtc.clearIRQ();
    M5.Rtc.setAlarmIRQ(55);
    M5.Power.powerOff();
}

void loop(void) {
    delay(100);
}