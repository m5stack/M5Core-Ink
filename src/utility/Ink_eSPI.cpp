#include "Ink_eSPI.h"

void Ink_eSPI::begin() {
    M5GFX::begin();
    M5GFX::setEpdMode(epd_mode_t::epd_fastest);
    M5GFX::invertDisplay(true);
    M5GFX::clear(TFT_BLACK);
    _isInit = true;
    _width  = 200;
    _height = 200;
}

int Ink_eSPI::clear(int mode) {
    M5GFX::clear();
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
        Serial.printf("bitsize: %d\r\n", _bitsize);
        Serial.printf("pixsize: %d\r\n", _pixsize);
        uint8_t *data = (uint8_t *)malloc(_pixsize);
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
        Serial.println("push~");
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

void Ink_eSPI::switchMode(int mode) {
}

void Ink_eSPI::setDrawAddr(uint16_t posx, uint16_t posy, uint16_t width,
                           uint16_t height) {
}

uint8_t Ink_eSPI::getPix(uint16_t posX, uint16_t posY) {
    /*
    uint8_t data = _lastbuff[posX * posY / 8];
    if( data & (0x80 >> (posX * posY % 8)))
    {
        return 1;
    }
    return 0;
    */
    int32_t pixNum = _width * posY + posX;
    uint8_t data   = _lastbuff[pixNum / 8];
    uint8_t mark   = (0x80 >> (pixNum % 8));
    if (data & mark) {
        return 1;
    }
    return 0;
}

void Ink_eSPI::deepSleep() {
    // waitbusy();
    // startWrite();
    // writeCMD(0X50);
    // writeData(0xf7);
    // waitbusy();
    // writeCMD(0X02);  // power off
    // waitbusy(5000);
    // writeCMD(0X07);  // deep sleep
    // writeData(0xA5);
    // endWrite();
}

void Ink_eSPI::powerHVON() {
    // waitbusy();
    // startWrite();
    // writeCMD(0X50);
    // writeData(0xd7);
    // waitbusy();
    // writeCMD(0X04);
    // endWrite();
}

void Ink_eSPI::powerHVOFF() {
    // waitbusy();
    // startWrite();
    // writeCMD(0X50);
    // writeData(0xf7);
    // waitbusy();
    // writeCMD(0X02);
    // endWrite();
}