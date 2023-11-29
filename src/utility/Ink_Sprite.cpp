#include "Ink_Sprite.h"

int Ink_Sprite::creatSprite(uint16_t posX, uint16_t posY, uint16_t width,
                            uint16_t height, bool copyFromMem) {
    // if ((posX % 8 != 0) || (width % 8 != 0)) return -1;

    _posX   = posX;
    _posY   = posY;
    _width  = width;
    _height = height;
    if (M5Canvas::createSprite(width, height)) {
        Serial.println("createSprite success");
    } else {
        Serial.println("createSprite failed");
    };
    return 0;
}

void Ink_Sprite::clear(int cleanFlag) {
    M5Canvas::clear();
}

void Ink_Sprite::drawPix(uint16_t posX, uint16_t posY, uint8_t pixBit) {
    M5Canvas::drawPixel(posX, posY, pixBit ? 0x0000 : 0xFFFF);
}

void Ink_Sprite::FillRect(uint16_t posX, uint16_t posY, uint16_t width,
                          uint16_t height, uint8_t pixBit) {
    fillRect(posX, posY, width, height, pixBit);
}

void Ink_Sprite::drawFullBuff(uint8_t *buff, bool bitMode) {
    if (bitMode) {
        size_t _pixsize = _width * _height;
        size_t _bitsize = _pixsize / 8;
        uint8_t *data   = (uint8_t *)malloc(_pixsize);
        if (!data) {
            return;
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
        M5Canvas::pushImage(0, 0, _width, _height, data);
        free(data);
    } else {
        M5Canvas::pushImage(0, 0, _width, _height, buff);
    }
}

void Ink_Sprite::drawChar(uint16_t posX, uint16_t posY, char charData,
                          const lgfx::FixedBMPfont *fontPtr) {
    M5Canvas::drawChar(charData, posX, posY);
}

void Ink_Sprite::drawString(uint16_t posX, uint16_t posY, const char *charData,
                            const lgfx::FixedBMPfont *fontPtr) {
    M5Canvas::drawString(charData, posX, posY, fontPtr);
}

void Ink_Sprite::drawBuff(uint16_t posX, uint16_t posY, uint16_t width,
                          uint16_t height, uint8_t *imageDataptr) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8_t mark = 0x80 >> (y * width + x) % 8;
            if ((imageDataptr[(y * width + x) / 8]) & mark) {
                drawPix(x + posX, y + posY, 1);
            } else {
                drawPix(x + posX, y + posY, 0);
            }
        }
    }
}

int Ink_Sprite::pushSprite() {
    M5Canvas::pushSprite(_posX, _posY);
    return 0;
}

int Ink_Sprite::deleteSprite() {
    return 0;
}