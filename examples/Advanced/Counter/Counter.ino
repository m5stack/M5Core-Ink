/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with CoreInk sample source code
*                          配套  CoreInk 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/coreink
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/coreink
*
* Describe: Counter.
* Date: 2021/11/28
*******************************************************************************
*/

#include <M5CoreInk.h>
#include <Preferences.h>

Preferences preferences;
Ink_Sprite InkPageSprite(&M5.M5Ink);  //创建 M5Ink实例

char Strbuff[64];

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
    InkPageSprite.drawString(10, 10, "Counter");  //在图像区域内绘制字符串
    preferences.begin(
        "my-app",
        false);  // We will open storage in RW-mode (second parameter has to be
                 // false).
                 // 在perferences中创建叫my-app的空间,并以rw模式打开存储(第二个参数必须为false)

    // preferences.clear();  // Remove all preferences under the opened
    // namespace.清除preferences中所有的空间 preferences.remove("counter");  //
    // Or remove the counter key only.  只清除counter中的值

    unsigned int counter = preferences.getUInt(
        "counter",
        0);  // Get the counter value in current sapce, if the key does not
             // exist, return a default value of 0.
             // 在当前空间中读取counter的值(若不存在为0),并赋值给counter
    counter++;  // Increase counter by 1.  使计数器的值加一
    sprintf(Strbuff, "Current counter value:%u", counter);
    InkPageSprite.drawString(5, 40, Strbuff);
    preferences.putUInt(
        "counter",
        counter);  // Store the counter to the Preferences.  存储计数器的值
    preferences.end();  // Close the Preferences.  关闭Preferences
    InkPageSprite.drawString(10, 75, "Restart in 15 s");
    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上
    delay(15000);                // delay 10.  延迟10s
    ESP.restart();               // Restart.  重启
}
void loop() {
}
