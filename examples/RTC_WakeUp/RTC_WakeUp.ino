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

void setup() {
    M5.begin();                      // Initialize CoreInk. 初始化 CoreInk
    digitalWrite(LED_EXT_PIN, LOW);  //设置 LED_EXT_PIN 为低电平
    if (!M5.M5Ink.isInit()) {        //判断 M5Ink 是否初始化成功
        Serial.printf("Ink Init failed");
        while (1) delay(100);
    }
    M5.M5Ink.clear();  // clear the screen. 清屏
    delay(1000);
    // creat ink Sprite. 创建图像区域
    if (InkPageSprite.creatSprite(0, 0, 200, 200, true) != 0) {
        Serial.printf("Ink Sprite create failed");
    }
    InkPageSprite.drawString(
        10, 50, "Press PWR Btn for sleep");  //在图像区域内绘制字符串
    InkPageSprite.drawString(15, 80, "after 5 sec wakeup.");
    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上
}

void loop() {
    // Press PWR Btn for sleep , after 5 sec wakeup.
    // Press POWER Button for sleep, after 5 sec wake up.
    if (M5.BtnPWR.wasPressed()) {
        Serial.printf("Btn %d was pressed \r\n", BUTTON_PWR_PIN);
        M5.shutdown(5);  // Turn off the power and wake up the device through
        // RTC after the delay of 5 seconds.
        // 关闭电源,在延时5秒结束后通过RTC唤醒设备。
        // M5.shutdown(RTC_TimeTypeDef(0, 0, 5));
    }
    M5.update();                  // Refresh device button. 刷新设备按键
    if (M5.BtnUP.wasPressed()) {  // The program continues to execute after 5
                                  // seconds
        Serial.printf("Btn %d was pressed \r\n", BUTTON_UP_PIN);
    }
}