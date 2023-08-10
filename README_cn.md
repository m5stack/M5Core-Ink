# CoreInk Library

[![Arduino Compile](https://github.com/m5stack/M5Core-Ink/actions/workflows/arduino-action-coreink-compile.yml/badge.svg)](https://github.com/m5stack/M5Core-Ink/actions/workflows/arduino-action-paper-compile.yml)
[![Arduino Lint](https://github.com/m5stack/M5Core-Ink/actions/workflows/Arduino-Lint-Check.yml/badge.svg)](https://github.com/m5stack/M5Core-Ink/actions/workflows/Arduino-Lint-Check.yml)
[![Clang Format](https://github.com/m5stack/M5Core-Ink/actions/workflows/clang-format-check.yml/badge.svg)](https://github.com/m5stack/M5Core-Ink/actions/workflows/clang-format-check.yml)

[English](README.md) | 中文

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/coreink/coreink_01.webp" alt="CoreInk_Pic_01" width="350">

## 描述

**CoreInk** 是M5Stack推出的一款带有电子墨水屏(E-Ink)的主控设备，控制器采用ESP32-PICO-D4。正面嵌入了一块分辨率为200x200 @ 1.54"的电子墨水屏，支持黑/白显示。相对于普通的LCD的屏幕，电子墨水屏能够提供用户更好的文本阅读体验， 同时具有低功耗，掉电图像保持等特性。人机交互方面提供了拨轮开关，与物理按键, 集成LED指示灯与蜂鸣器。内置了390mAh锂电池，结合内部的RTC(BM8563)可实现定时休眠与唤醒功能，能够为设备提供较为优秀的续航能力。在机身的左侧和底部配有独立的电源按键与复位(RST)按键，方便使用与调试。开放了丰富的外设接口(HY2.0-4P、M-BUS、HAT模块接口)能够拓展各式各样的传感器设备，为后续的应用功能开发提供无限可能。

**注意事项**: 使用时请注意避免长时间高频刷新，建议刷新间隔为(15s/次), 请勿长时间暴露在紫外线下, 否则有可能对墨水屏造成不可逆的损害。

* **如果想要购买 CoreInk 的话，[点击这里](https://item.taobao.com/item.htm?spm=a1z10.5-c-s.w4002-22404213529.11.5d80e428hIJBNY&id=631373978142)**

<img class="pic" src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/coreink/coreink_02.webp" alt="CoreInk_Pic_01" width="350">

## 产品特性

- 基于 ESP32 开发,支持WiFi,蓝牙
- 内置4M Flash
- 低功耗显示面板
- 近180度可视角
- 人机交互接口
- 背面磁吸设计
- 内置锂电池
- 丰富的拓展接口

## 更多信息

- **API** 

   - [CoreInk Arduino API](http://docs.m5stack.com/zh_CN/api/coreink/system_api)

-  **Document**
   - [Arduino Quick Start](http://docs.m5stack.com/zh_CN/quick_start/coreink/arduino)
   - [Product Document](https://docs.m5stack.com/zh_CN/core/coreink)

## 相关链接

- **Datasheet** 
   - [ESP32](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/esp32_datasheet_cn.pdf)
   - [BM8563](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/BM8563_V1.1_cn.pdf)
   - [SY7088](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/SY7088-Silergy.pdf)
   - [GDEW0154M09](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/CoreInk-K048-GDEW0154M09%20V2.0%20Specification.pdf)

