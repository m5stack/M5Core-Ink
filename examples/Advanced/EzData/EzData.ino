/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with CoreInk sample source code
*                          配套  CoreInk 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/coreink
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/coreink
*
* Describe: EzData
* Date: 2021/11/27
*******************************************************************************
*/
#include "M5CoreInk.h"
#include "M5_EzData.h"

Ink_Sprite InkPageSprite(&M5.M5Ink);  //创建 M5Ink实例

// Configure the name and password of the connected wifi and your token.
// 配置所连接wifi的名称、密码以及你的token
const char* ssid     = "Explore-F";
const char* password = "xingchentansuo123";
const char* token    = "JT8H8eSd0A0pKajNzGm2tDL2H6mjIVLc";

void setup() {
    M5.begin();
    digitalWrite(LED_EXT_PIN, LOW);  //设置 LED_EXT_PIN 为低电平
    if (!M5.M5Ink.isInit()) {        //判断 M5Ink 是否初始化成功
        Serial.printf("Ink Init faild");
        while (1) delay(100);
    }
    M5.M5Ink.clear();  // clear the screen. 清屏
    delay(1000);
    // creat ink Sprite. 创建图像区域
    if (InkPageSprite.creatSprite(0, 0, 200, 200, true) != 0) {
        Serial.printf("Ink Sprite creat faild");
    }
    if (setupWifi(ssid, password)) {  // Connect to wifi.  连接到wifi
        InkPageSprite.drawString(
            10, 10, "Success connecting to ");  //在图像区域内绘制字符串
        InkPageSprite.drawString(10, 25, ssid);  //在图像区域内绘制字符串
    } else {
        InkPageSprite.drawString(10, 10,
                                 "Connecting failed");  //在图像区域内绘制字符串
    }
    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上
}

void loop() {
    // Save the data 20 to the top of the testData topic queue.  保存数据20至
    // testData 队列首位
    if (setData(token, "testData", 20)) {
        InkPageSprite.drawString(10, 50, "Success sending data");
    } else {
        InkPageSprite.drawString(10, 50, "Fail to save data");
    }
    delay(10000);
    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上

    // Save 3 data in sequence to the first place of testList. 依次保存3个数据至
    // testList首位
    for (int i = 0; i < 3; i++) {
        if (addToList(token, "testList", i)) {
            InkPageSprite.drawString(10, 65, "Success sending data");
        } else {
            InkPageSprite.drawString(10, 65, "Fail to save data");
        }
        delay(100);
    }
    delay(10000);
    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上
    // Get a piece of data from a topic and store the value in result.  从一个
    // topic中获取一个数据,并将值存储在 result
    int result = 0;
    if (getData(token, "testData", result)) {
        InkPageSprite.drawString(10, 80, "Success get data");
    } else {
        InkPageSprite.drawString(10, 80, "Fail to get data");
    }
    delay(10000);
    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上

    // Remove data
    if (removeData(token, "testData"))
        InkPageSprite.drawString(10, 95, "Success remove data");
    else
        InkPageSprite.drawString(10, 95, "Fail to remove data");

    if (removeData(token, "testList"))
        InkPageSprite.drawString(10, 110, "Success remove data");
    else
        InkPageSprite.drawString(10, 110, "Fail to remove data");
    delay(10000);
    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上
    delay(10000);
    InkPageSprite.clear();  // clear the screen. 清屏
}
