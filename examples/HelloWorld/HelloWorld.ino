/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with CoreInk sample source code
*                          配套  CoreInk 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/coreink
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/coreink
*
* Describe: Hello World
* Date: 2021/11/14
*******************************************************************************
*/
#include "M5CoreInk.h"

Ink_Sprite InkPageSprite(&M5.M5Ink);  //创建 M5Ink实例

/* After CoreInk is started or reset
  the program in the setUp () function will be run, and this part will only be
  run once. 在 CoreInk
  启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin();                // Initialize CoreInk. 初始化 CoreInk
    if (!M5.M5Ink.isInit()) {  // check if the initialization is successful.
                               // 检查初始化是否成功
        Serial.printf("Ink Init faild");
        while (1) delay(100);
    }
    M5.M5Ink.clear();  // clear the screen. 清屏
    delay(1000);
    // creat ink Sprite. 创建图像区域
    if (InkPageSprite.creatSprite(0, 0, 200, 200, true) != 0) {
        Serial.printf("Ink Sprite creat faild");
    }
    InkPageSprite.drawString(35, 50, "Hello World!");  // draw string.
                                                       // 绘制字符串
    InkPageSprite.pushSprite();  // push the sprite.  推送图片
}

void loop() {
}