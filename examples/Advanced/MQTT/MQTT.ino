/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with CoreInk sample source code
*                          配套  CoreInk 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/coreink
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/coreink
*
* Describe: MQTT.
* Date: 2021/11/28
*******************************************************************************
*/

#include <M5CoreInk.h>
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);
Ink_Sprite InkPageSprite(&M5.M5Ink);

// Configure the name and password of the connected wifi and your MQTT Serve
// host.  配置所连接wifi的名称、密码以及你MQTT服务器域名
const char* ssid        = "Explore-F";
const char* password    = "xingchentansuo123";
const char* mqtt_server = "mqtt.m5stack.com";

#define MSG_BUFFER_SIZE (50)
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setupWifi();
void callback(char* topic, byte* payload, unsigned int length);
void reConnect();

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
    InkPageSprite.drawString(10, 10, "MQTT");  //在图像区域内绘制字符串
    setupWifi();
    client.setServer(mqtt_server,
                     1883);  // Sets the server details.  配置所连接的服务器
    client.setCallback(
        callback);  // Sets the message callback function.  设置消息回调函数
    InkPageSprite.pushSprite();  //将图像区域内的内容推送到屏幕上
}

void loop() {
    if (!client.connected()) {
        reConnect();
    }
    client.loop();  // This function is called periodically to allow clients to
                    // process incoming messages and maintain connections to the
                    // server.
    //定期调用此函数，以允许主机处理传入消息并保持与服务器的连接

    unsigned long now =
        millis();  // Obtain the host startup duration.  获取主机开机时长
    if (now - lastMsg > 2000) {
        lastMsg = now;
        ++value;
        snprintf(msg, MSG_BUFFER_SIZE, "hello world #%d",
                 value);  // Format to the specified string and store it in MSG.
                          // 格式化成指定字符串并存入msg中
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("M5Stack", msg);  // Publishes a message to the specified
                                         // topic.  发送一条消息至指定话题
    }
}

void setupWifi() {
    delay(10);
    Serial.printf("Connecting to %s", ssid);
    WiFi.mode(
        WIFI_STA);  // Set the mode to WiFi station mode.  设置模式为WIFI站模式
    WiFi.begin(ssid, password);  // Start Wifi connection.  开始wifi连接

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.printf("\nSuccess\n");
    InkPageSprite.drawString(
        10, 25, "Success connecting wifi ");  //在图像区域内绘制字符串
    InkPageSprite.drawString(10, 40,
                             "Please see the serial");  //在图像区域内绘制字符串
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void reConnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID.  创建一个随机的客户端ID
        String clientId = "M5Stack-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect.  尝试重新连接
        if (client.connect(clientId.c_str())) {
            Serial.printf("\nSuccess\n");
            // Once connected, publish an announcement to the topic.
            // 一旦连接，发送一条消息至指定话题
            client.publish("M5Stack", "hello world");
            // ... and resubscribe.  重新订阅话题
            client.subscribe("M5Stack");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
            delay(5000);
        }
    }
}
