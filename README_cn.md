# CoreInk Library

[English](README.md) | 中文

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/coreink/coreink_01.webp" alt="CoreInk_Pic_01" width="350">

## 描述

**CoreInk** 是M5Stack推出的一款带有电子墨水屏(E-Ink)的主控设备，控制器采用ESP32-PICO-D4。正面嵌入了一块分辨率为200x200 @ 1.54"的电子墨水屏，支持黑/白显示。相对于普通的LCD的屏幕，电子墨水屏能够提供用户更好的文本阅读体验， 同时具有低功耗，掉电图像保持等特性。人机交互方面提供了拨轮开关，与物理按键, 集成LED指示灯与蜂鸣器。内置了390mAh锂电池，结合内部的RTC(BM8563)可实现定时休眠与唤醒功能，能够为设备提供较为优秀的续航能力。在机身的左侧和底部配有独立的电源按键与复位(RST)按键，方便使用与调试。开放了丰富的外设接口(HY2.0-4P、M-BUS、HAT模块接口)能够拓展各式各样的传感器设备，为后续的应用功能开发提供无限可能。

?>注意事项: 使用时请注意避免长时间高频刷新，建议刷新间隔为(15s/次), 请勿长时间暴露在紫外线下, 否则有可能对墨水屏造成不可逆的损害。

## 管脚映射

**墨水屏幕**

屏幕像素：200x200

<table>
 <tr><td>ESP32 Chip</td><td>GPIO4</td><td>GPIO0</td><td>GPIO15</td><td>GPIO9</td><td>GPIO18</td><td>GPIO23</td></tr>
 <tr><td>GDEW0154M09</td><td>BUSY</td><td>RST</td><td>D/C</td><td>CS</td><td>SCK</td><td>MOSI</td></tr>
</table>

**拨轮开关 & 物理按键 & LED & 蜂鸣器**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO37</td><td>GPIO38</td><td>GPIO39</td><td>GPIO5</td><td>GPIO10</td><td>GPIO2</td></tr>
 <tr><td>拨轮开关</td><td>右</td><td>中</td><td>左</td><td>/</td><td>/</td><td>/</td></tr>
 <tr><td>物理按键</td><td>/</td><td>/</td><td>/</td><td>物理按键</td><td>/</td><td>/</td></tr>
 <tr><td>LED</td><td>/</td><td>/</td><td>/</td><td>/</td><td>LED</td><td>/</td></tr>
 <tr><td>蜂鸣器</td><td>/</td><td>/</td><td>/</td><td>/</td><td>/</td><td>蜂鸣器</td></tr>
</table>

**USB转串口下载**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO1</td><td>GPIO3</td></tr>
 <tr><td>CP2104</td><td>RXD</td><td>TXD</td></tr>
</table>

**内部I2C连接**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO21</td><td>GPIO22</td></tr>
 <tr><td>BM8563</td><td>SDA</td><td>SCL</td></tr>
</table>

## Coreink-HY2.0 4P端口

<table>
      <thead>
         <th>PORT</th>
         <th>PIN</th>
         <th>备注:</th>
      </thead>
      <tbody>
      <tr>
         <td>EXT-PORT</td>
         <td>G32/33</td>
         <td>I2C</td>
      </tr>
    </tbody>
</table>


## 相关链接

- **Datasheet** 
   - [ESP32](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/esp32_datasheet_cn.pdf)
   - [BM8563](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/BM8563_V1.1_cn.pdf)
   - [SY7088](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/SY7088-Silergy.pdf)
   - [GDEW0154M09](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/CoreInk-K048-GDEW0154M09%20V2.0%20Specification.pdf)

- **API** 

   - [Arduino API](http://docs.m5stack.com/#/zh_CN/arduino/arduino_home_page)

-  **Document**
   - [Arduino Quick Start](http://docs.m5stack.com/#/en/quick_start/coreink/quick_start_arduino)
   - [Product Document](https://docs.m5stack.com/en/core/coreink)
