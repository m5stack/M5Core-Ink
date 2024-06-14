/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with CoreInk sample source code
*                          配套  CoreInk 示例源代码
* Visit for more information：https://docs.m5stack.com/en/core/coreink
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/coreink
*
* Describe: RTC example.  RTC示例
* Date: 2022/6/30
*******************************************************************************
*/
#include "M5CoreInk.h"

Ink_Sprite InkPageSprite(&M5.M5Ink);  //创建 M5Ink实例

RTC_TimeTypeDef RTCtime;
RTC_DateTypeDef RTCDate;

char timeStrbuff[64];

void flushTime() {
    M5.rtc.GetTime(&RTCtime);  // Get RTC time. 获取RTC时间
    M5.rtc.GetDate(&RTCDate);  // Get RTC date. 获取RTC日期
    sprintf(timeStrbuff, "%d/%02d/%02d %02d:%02d:%02d", RTCDate.Year,
            RTCDate.Month, RTCDate.Date, RTCtime.Hours, RTCtime.Minutes,
            RTCtime.Seconds);
    InkPageSprite.drawString(10, 100, timeStrbuff);  // Draw time. 绘制时间
    InkPageSprite.pushSprite();  // push the sprite. 推送图片
}

void setupTime() {
    RTCtime.Hours   = 23;
    RTCtime.Minutes = 33;
    RTCtime.Seconds = 33;
    M5.rtc.SetTime(&RTCtime);  // Set RTC time. 设置RTC时间

    RTCDate.Year  = 2020;
    RTCDate.Month = 11;
    RTCDate.Date  = 6;
    M5.rtc.SetDate(&RTCDate);  // Set RTC date. 设置RTC日期
}

void setup() {
    M5.begin();                // Initialize CoreInk. 初始化 CoreInk
    if (!M5.M5Ink.isInit()) {  // check if the initialization is successful.
                               // 检查初始化是否成功
        Serial.printf("Ink Init failed");
        while (1) delay(100);
    }
    M5.M5Ink.clear();  // clear the screen. 清屏
    delay(1000);
    // creat ink Sprite. 创建图像区域
    if (InkPageSprite.creatSprite(0, 0, 200, 200, true) != 0) {
        Serial.printf("Ink Sprite create failed");
    }
    setupTime();
}

void loop() {
    flushTime();
    delay(15000);
}