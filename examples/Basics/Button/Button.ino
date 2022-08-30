/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with CoreInk sample source code
*                          配套  CoreInk 示例源代码
* Visit for more information：https://docs.m5stack.com/en/core/coreink
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/coreink
*
* Product: Button example.  按键示例
* Date: 2022/6/30
*******************************************************************************
*/
#include "M5CoreInk.h"

Ink_Sprite InkPageSprite(&M5.M5Ink);  //创建 M5Ink实例

void ButtonTest(char* str) {
    InkPageSprite.clear();                  // clear the screen.  清屏
    InkPageSprite.drawString(35, 59, str);  // draw the string.  绘制字符串
    InkPageSprite.pushSprite();             // push the sprite.  推送图片
    delay(2000);
}

/* After CoreInk is started or reset
  the program in the setUp () function will be run, and this part will only be
  run once. 在 CoreInk
  启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin();                // Initialize CoreInk. 初始化 CoreInk
    if (!M5.M5Ink.isInit()) {  // check if the initialization is successful.
                               // 检查初始化是否成功
        Serial.printf("Ink Init faild");
    }
    M5.M5Ink.clear();  // Clear the screen. 清屏
    delay(1000);
    // creat ink Sprite. 创建图像区域
    if (InkPageSprite.creatSprite(0, 0, 200, 200, true) != 0) {
        Serial.printf("Ink Sprite create faild");
    }
    InkPageSprite.drawString(20, 20, "Hello Core-INK");
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    if (M5.BtnUP.wasPressed())
        ButtonTest("Btn UP Pressed");  // Scroll wheel up.  拨轮向上滚动
    if (M5.BtnDOWN.wasPressed())
        ButtonTest("Btn DOWN Pressed");  // Trackwheel scroll down. 拨轮向下滚动
    if (M5.BtnMID.wasPressed())
        ButtonTest("Btn MID Pressed");  // Dial down.  拨轮按下
    if (M5.BtnEXT.wasPressed())
        ButtonTest("Btn EXT Pressed");  // Top button press.  顶部按键按下
    if (M5.BtnPWR.wasPressed()) {  // Right button press.  右侧按键按下
        ButtonTest("Btn PWR Pressed");
        M5.shutdown();  // Turn off the power, restart it, you need to wake up
                        // through the PWR button.
                        // 关闭电源,再次启动需要通过PWR按键唤醒
    }
    M5.update();  // Refresh device button. 刷新设备按键
}
