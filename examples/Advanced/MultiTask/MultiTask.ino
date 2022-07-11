/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with CoreInk sample source code
*                          配套  CoreInk 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/coreink
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/coreink
*
* Describe: MultiTask.
* Date: 2021/11/28
*******************************************************************************
*/

#include <M5CoreInk.h>

Ink_Sprite InkPageSprite(&M5.M5Ink);  //创建 M5Ink实例

void task1(void* pvParameters) {  // Define the tasks to be executed in
                                  // thread 1.  定义线程1内要执行的任务
    while (1) {  // Keep the thread running.  使线程一直运行
        Serial.print("task1 Uptime (ms): ");
        Serial.println(millis());  // The running time of the serial port
                                   // printing program.  串口打印程序运行的时间
        delay(
            100);  // With a delay of 100ms, it can be seen in the serial
                   // monitor that every 100ms, thread 1 will be executed once.
                   // 延迟100ms,在串口监视器内可看到每隔100ms,线程1就会被执行一次
    }
}

void task2(void* pvParameters) {
    while (1) {
        Serial.print("task2 Uptime (ms): ");
        Serial.println(millis());
        delay(200);
    }
}

void task3(void* pvParameters) {
    while (1) {
        Serial.print("task3 Uptime (ms): ");
        Serial.println(millis());
        delay(1000);
    }
}

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
    InkPageSprite.drawString(10, 10, "MultiTask");  //在图像区域内绘制字符串
    InkPageSprite.drawString(10, 25, "Please see the serial");

    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上
    // Creat Task1.  创建线程1
    xTaskCreatePinnedToCore(
        task1,    // Function to implement the task.
                  // 线程对应函数名称(不能有返回值)
        "task1",  //线程名称
        4096,     // The size of the task stack specified as the number of *
                  // bytes.任务堆栈的大小(字节)
        NULL,     // Pointer that will be used as the parameter for the task *
                  // being created.  创建作为任务输入参数的指针
        1,        // Priority of the task.  任务的优先级
        NULL,     // Task handler.  任务句柄
        0);  // Core where the task should run.  将任务挂载到指定内核

    // Task 2
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 2, NULL, 0);

    // Task 3
    xTaskCreatePinnedToCore(task3, "task3", 4096, NULL, 3, NULL, 0);
}

void loop() {
}