# CoreInk Library

English | [中文](README_cn.md)

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/coreink/coreink_01.webp" alt="CoreInk_Pic_01" width="350">

## Description

**CoreInk** is a brand new E-ink display in the M5Stack cores range. Controlled by the ESP32-PICO-D4 This new device includes a 200x200 1.54" Black and White E-Ink Display. Compared to a regular LCD，E-ink displays are easier on the eyes, which makes them a great choice for reading or viewing for longer periods. Other benefits are the low power consumption and the ability to retain the image even if power to the display is terminated。For control the CoreInk integrates an multi-function button,A physical button, integrated status LED and buzzer.The device also includes a 390mAh Lipo，RTC(BM8563)for controlling accurate timing and deep sleep funcionality. CoreInk features independent reset and power buttons，expansion ports(HY2.0-4P、M-BUS、HAT expansion)for attaching external sensors to expand functionailty，for unlimited possibilities。

?>Warning: Please avoid using high refresh rates，reccommended refresh rate is(15s/per refresh), Do not expose to ultraviolet rays for a long time, otherwise it may cause irreversible damage to the ink screen.

## Pin Mapping

**E-Ink Display**

Screen Resolution：200x200

<table>
 <tr><td>ESP32 Chip</td><td>GPIO4</td><td>GPIO0</td><td>GPIO15</td><td>GPIO9</td><td>GPIO18</td><td>GPIO23</td></tr>
 <tr><td>GDEW0154M09</td><td>BUSY</td><td>RST</td><td>D/C</td><td>CS</td><td>SCK</td><td>MOSI</td></tr>
</table>

**Multi-function button & Physical Button & LED & Buzzer**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO37</td><td>GPIO38</td><td>GPIO39</td><td>GPIO5</td><td>GPIO10</td><td>GPIO2</td></tr>
 <tr><td>Multi-function button</td><td>Left position</td><td>Button press</td><td>Right position</td><td>/</td><td>/</td><td>/</td></tr>
 <tr><td>Physical Button</td><td>/</td><td>/</td><td>/</td><td>Physical Button</td><td>/</td><td>/</td></tr>
 <tr><td>LED</td><td>/</td><td>/</td><td>/</td><td>/</td><td>LED</td><td>/</td></tr>
 <tr><td>Buzzer</td><td>/</td><td>/</td><td>/</td><td>/</td><td>/</td><td>Buzzer</td></tr>
</table>

**USB Serial**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO1</td><td>GPIO3</td></tr>
 <tr><td>CP2104</td><td>RXD</td><td>TXD</td></tr>
</table>


**Internal I2C Connection**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO21</td><td>GPIO22</td></tr>
 <tr><td>BM8563</td><td>SDA</td><td>SCL</td></tr>
</table>


## Coreink-HY2.0 4P Port

<table>
      <thead>
         <th>PORT</th>
         <th>PIN</th>
         <th>Protocol:</th>
      </thead>
      <tbody>
      <tr>
         <td>EXT-PORT</td>
         <td>G32/33</td>
         <td>I2C</td>
      </tr>
    </tbody>
</table>

## Related Link

- **Datasheet** 
   - [ESP32](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/esp32_datasheet_cn.pdf)
   - [BM8563](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/BM8563_V1.1_cn.pdf)
   - [SY7088](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/SY7088-Silergy.pdf)
   - [GDEW0154M09](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/CoreInk-K048-GDEW0154M09%20V2.0%20Specification.pdf)

-  **API**
   - [Arduino API](http://docs.m5stack.com/#/en/arduino/arduino_home_page)


-  **Document**
   - [Arduino Quick Start](http://docs.m5stack.com/#/en/quick_start/coreink/quick_start_arduino)
   - [Product Document](https://docs.m5stack.com/en/core/coreink)
