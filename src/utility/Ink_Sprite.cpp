#include "Ink_Sprite.h"

Ink_Sprite::Ink_Sprite(Ink_eSPI *dev) {
    _dev = dev;
}

Ink_Sprite::~Ink_Sprite() {
    deleteSprite();
}

int Ink_Sprite::creatSprite(uint16_t posX, uint16_t posY, uint16_t width,
                            uint16_t height, bool copyFromMem) {
    if ((posX % 8 != 0) || (width % 8 != 0)) return -1;

    _posX    = posX;
    _posY    = posY;
    _width   = width;
    _height  = height;
    _pixSize = width * height / 8;

    _spriteBuff = (uint8_t *)malloc(sizeof(uint8_t) * _pixSize);
    if (_spriteBuff == nullptr) return -1;

    _lastBuff = (uint8_t *)malloc(sizeof(uint8_t) * _pixSize);
    if (_lastBuff == nullptr) return -1;

    memset(_spriteBuff, 0xff, sizeof(uint8_t) * _pixSize);
    memset(_lastBuff, 0xff, sizeof(uint8_t) * _pixSize);

    isCreat = true;

    if (copyFromMem) {
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                int32_t pixNum = _width * y + x;
                if (_dev->getPix(_posX + x, _posY + y) == 0) {
                    _lastBuff[pixNum / 8] &= ~(0x80 >> (pixNum % 8));
                } else {
                    _lastBuff[pixNum / 8] |= (0x80 >> (pixNum % 8));
                }
            }
        }
    }

    return 0;
}

void Ink_Sprite::clear(int cleanFlag) {
    if (!isCreat) return;

    for (int i = 0; i < _pixSize; i++) {
        if (cleanFlag & CLEAR_DRAWBUFF) _spriteBuff[i] = 0xFF;
        if (cleanFlag & CLEAR_LASTBUFF) _lastBuff[i] = 0xFF;
    }
}

void Ink_Sprite::drawPix(uint16_t posX, uint16_t posY, uint8_t pixBit) {
    if (!isCreat) return;

    int32_t pixNum = _width * posY + posX;

    if (pixBit == 0) {
        _spriteBuff[pixNum / 8] &= ~(0x80 >> (pixNum % 8));
    } else {
        _spriteBuff[pixNum / 8] |= (0x80 >> (pixNum % 8));
    }
}

void Ink_Sprite::FillRect(uint16_t posX, uint16_t posY, uint16_t width,
                          uint16_t height, uint8_t pixBit) {
    if (!isCreat) return;

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) drawPix(posX + x, posY + y, pixBit);
}

void Ink_Sprite::drawFullBuff(uint8_t *buff, bool bitMode) {
    if (!isCreat) return;

    for (int i = 0; i < _pixSize; i++) {
        _spriteBuff[i] = (bitMode) ? buff[i] : ~buff[i];
    }
}

void Ink_Sprite::drawChar(uint16_t posX, uint16_t posY, char charData,
                          Ink_eSPI_font_t *fontPtr) {
    if (!isCreat) return;

    charData -= 0x20;

    for (int y = 0; y < fontPtr->_height; y++) {
        for (int x = 0; x < fontPtr->_width; x++) {
            uint8_t mark = 0x80 >> (y * fontPtr->_width + x) % 8;
            if ((fontPtr->_fontptr[charData * fontPtr->_fontSize +
                                   (y * fontPtr->_width + x) / 8]) &
                mark) {
                drawPix(x + posX, y + posY, 0);
            } else {
                drawPix(x + posX, y + posY, 1);
            }
        }
    }
}

void Ink_Sprite::drawString(uint16_t posX, uint16_t posY, const char *charData,
                            Ink_eSPI_font_t *fontPtr) {
    if (!isCreat) return;

    int _posX = posX;
    while (*charData != '\0') {
        drawChar(_posX, posY, *charData, fontPtr);
        _posX += fontPtr->_width;

        charData++;
    }
}

void Ink_Sprite::drawBuff(uint16_t posX, uint16_t posY, uint16_t width,
                          uint16_t height, uint8_t *imageDataptr) {
    if (!isCreat) return;

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
    if (!isCreat) return -1;

    if (_dev->getMode() != INK_PARTIAL_MODE) {
        _dev->clearDSRAM();
        _dev->switchMode(INK_PARTIAL_MODE);
    }
    _dev->setDrawAddr(_posX, _posY, _width, _height);
    _dev->drawBuff(_lastBuff, _spriteBuff, _pixSize);

    return 0;
}

int Ink_Sprite::deleteSprite() {
    if (!isCreat) return -1;

    free(_spriteBuff);
    free(_lastBuff);

    return 0;
}