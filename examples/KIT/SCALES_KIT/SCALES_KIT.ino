/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5CoreInk sample source code
*                          配套  M5CoreInk 示例源代码
* Visit the website for more
information：https://docs.m5stack.com/en/app/scales_kit
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/app/scales_kit
*
* Product:  SCALES KIT WEIGHT UNIT EXAMPLE.
* Date: 2022/02/23
*******************************************************************************
Connect WEIGHT UNIT to port A (G32/33)
Calibration Instructions: Push the roller switch to tare up (0g calibration)
when there is no load. Press the middle button of the wheel switch, push left
and right to switch the standard weight value and put down the corresponding
weight, and press the middle button of the wheel to confirm to calibrate.
confirm for calibration.
将WEIGHT UNIT连接至端口A（G32/33）
校准说明：无负重情况下推动滚轮开关向上去皮重(0g 校准)，
按下滚轮开关中间按键，左右推动切换标准重量值并放下对应重量砝码，按下滚轮中间按键comfirm进行校准。
  Libraries:
  - [HX711](https://github.com/bogde/HX711)

*/

#include <M5CoreInk.h>
#include <M5GFX.h>
#include "HX711.h"

M5GFX display;
M5Canvas canvas(&display);

// HX711 related pin Settings.  HX711 相关引脚设置
#define LOADCELL_DOUT_PIN 33
#define LOADCELL_SCK_PIN  32

HX711 scale;

void setup() {
    M5.begin();

    display.begin();

    if (display.isEPD()) {
        display.setEpdMode(epd_mode_t::epd_fastest);
        display.invertDisplay(true);
        display.clear(TFT_BLACK);
    }
    if (display.width() < display.height()) {
        display.setRotation(display.getRotation() ^ 1);
    }

    canvas.createSprite(display.width(), display.height());
    canvas.setTextDatum(MC_DATUM);
    canvas.setTextSize(1);
    canvas.setFont(&fonts::lgfxJapanGothic_16);
    canvas.drawString("Calibration sensor....", 100, 100);
    canvas.pushSprite(0, 0);
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    // The scale value is the adc value corresponding to 1g
    scale.set_scale(27.61f);  // set scale
    scale.tare();             // auto set offset
}

char info[100];

float last_weight = 0;

void loop() {
    float weight = scale.get_units(20) / 1000.0;
    if (weight != last_weight) {
        canvas.clear();
        canvas.setTextSize(1);
        canvas.drawString("press MID calibration mode", 100, 20);
        canvas.drawString("press EXT  0g calibration", 100, 40);
        canvas.setTextSize(2);
        if (weight >= 0) {
            Serial.printf("%.2f", weight);
            sprintf(info, "%.2f", weight);
            canvas.drawString(String(info) + "kg", 100, 100);
        } else {
            canvas.drawString("0.00kg", 100, 100);
        }
        canvas.pushSprite(0, 0);
        last_weight = weight;
        delay(500);
    }
    M5.update();
    if (M5.BtnEXT.wasPressed()) {
        canvas.clear();
        canvas.setTextSize(1);
        scale.tare();
        canvas.drawString("0g calibration!", 100, 100);
        canvas.pushSprite(0, 0);
        delay(500);
    }
    if (M5.BtnMID.wasPressed()) {
        long kg = 5;
        while (1) {
            M5.update();
            canvas.clear();
            canvas.setTextSize(1);
            canvas.drawString("calibration:" + String(kg) + "kg", 100, 100);
            canvas.drawString("press MID comfirm", 100, 20);
            canvas.drawString("press UP/DOWN change calibration value", 100,
                              40);
            canvas.pushSprite(0, 0);
            if (M5.BtnDOWN.isPressed()) {
                kg--;
            }
            if (M5.BtnUP.isPressed()) {
                kg++;
            }
            if (M5.BtnMID.wasPressed()) {
                break;
            }
            delay(100);
        }
        long kg_adc = scale.read_average(20);
        kg_adc      = kg_adc - scale.get_offset();
        scale.set_scale(kg_adc / (kg * 1000.0));
        canvas.drawString("Set Scale: " + String(kg_adc / (kg * 1000.0)), 100,
                          100);
        canvas.pushSprite(0, 0);
        delay(500);
    }
}
