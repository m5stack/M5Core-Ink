#include "Ink_eSPI.h"

void Ink_eSPI::begin() {
    M5GFX::begin();
    M5GFX::setEpdMode(epd_mode_t::epd_text);
    M5GFX::invertDisplay(true);
    M5GFX::clear(TFT_BLACK);
    _isInit = true;
    _width  = 200;
    _height = 200;
}

int Ink_eSPI::clear(int mode) {
    M5GFX::clear(TFT_BLACK);
    M5GFX::fillScreen(TFT_BLACK);
    return 0;
}

[[deprecated("clearDSRAM is deprecated")]] int Ink_eSPI::clearDSRAM() {
    M5GFX::clear();
    return 0;
}

int Ink_eSPI::drawBuff(uint8_t *buff, bool bitMode) {
    if (bitMode) {
        size_t _pixsize = _width * _height;
        size_t _bitsize = _pixsize / 8;
        uint8_t *data   = (uint8_t *)malloc(_pixsize);
        if (!data) {
            return -1;
        }
        for (size_t i = 0; i < _bitsize; i++) {
            uint8_t _byte = buff[i];
            for (size_t j = 0; j < 8; j++) {
                size_t index = i * 8 + j;
                if (((_byte << j) & 0x80) == 0x80) {
                    data[index] = 0x00;
                } else {
                    data[index] = 0xff;
                }
            }
        }
        M5GFX::pushImage(0, 0, _width, _height, data);
        free(data);
    } else {
        M5GFX::pushImage(0, 0, _width, _height, buff);
    }

    return 0;
}

int Ink_eSPI::drawBuff(uint8_t *lastbuff, uint8_t *buff, size_t size) {
    M5GFX::pushImage(0, 0, _width, _height, buff);
    return 0;
}

bool Ink_eSPI::isInit() {
    return _isInit;
}

void Ink_eSPI::switchMode(epd_mode_t mode) {
    M5GFX::setEpdMode(epd_mode_t::epd_quality);
}

void Ink_eSPI::deepSleep() {
    M5GFX::sleep();
}

void Ink_eSPI::powerHVON() {
    M5GFX::powerSaveOff();
}

void Ink_eSPI::powerHVOFF() {
    M5GFX::powerSaveOn();
}