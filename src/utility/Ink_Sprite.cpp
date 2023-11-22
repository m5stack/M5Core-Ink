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
    drawPixel(posX, posY, pixBit ? 0xffff : 0x0000);
}

void Ink_Sprite::FillRect(uint16_t posX, uint16_t posY, uint16_t width,
                          uint16_t height, uint8_t pixBit) {
    fillRect(posX, posY, width, height, pixBit);
}

void Ink_Sprite::drawFullBuff(uint8_t *buff, bool bitMode) {
}

void Ink_Sprite::drawChar(uint16_t posX, uint16_t posY, char charData,
                          const lgfx::FixedBMPfont *fontPtr) {
    M5Canvas::drawChar(charData, posX, posY);
}

void Ink_Sprite::drawString(uint16_t posX, uint16_t posY, const char *charData,
                            const lgfx::FixedBMPfont *fontPtr) {
    M5Canvas::drawString(charData, posX, posY);
}

void Ink_Sprite::drawBuff(uint16_t posX, uint16_t posY, uint16_t width,
                          uint16_t height, uint8_t *imageDataptr) {
    drawBitmap(posX, posY, imageDataptr, width, height, 1);
}

int Ink_Sprite::pushSprite() {
    M5Canvas::pushSprite(_posX, _posY);
    return 0;
}

int Ink_Sprite::deleteSprite() {
    return 0;
}