#ifndef _INK_SPRITE_H_
#define _INK_SPRITE_H_

#include "Ink_eSPI.h"

#define CLEAR_DRAWBUFF 0x01
#define CLEAR_LASTBUFF 0x02

class Ink_Sprite : private Ink_eSPI {
   public:
   public:
    Ink_Sprite(Ink_eSPI* dev);
    ~Ink_Sprite();

    int creatSprite(uint16_t posX, uint16_t posY, uint16_t width = 200,
                    uint16_t height = 200, bool copyFromMem = true);

    int pushSprite();
    int deleteSprite();

    void clear(int cleanFlag = CLEAR_DRAWBUFF);
    void drawPix(uint16_t posX, uint16_t posY, uint8_t pixBit);
    void FillRect(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height,
                  uint8_t pixBit);

    void drawFullBuff(uint8_t* buff, bool bitMode = true);
    void drawBuff(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height,
                  uint8_t* imageDataptr);

    void drawChar(uint16_t posX, uint16_t posY, char charData,
                  Ink_eSPI_font_t* fontPtr = &AsciiFont8x16);
    void drawString(uint16_t posX, uint16_t posY, const char* charData,
                    Ink_eSPI_font_t* fontPtr = &AsciiFont8x16);

    uint8_t* getSpritePtr() {
        return _spriteBuff;
    }

    uint16_t width() {
        return _width;
    }
    uint16_t height() {
        return _height;
    }
    uint16_t posX() {
        return _posX;
    }
    uint16_t posY() {
        return _posY;
    }

   private:
    Ink_eSPI* _dev;
    bool isCreat = false;
    uint16_t _posX, _posY;
    uint16_t _width, _height;
    uint16_t _pixSize;

    uint8_t* _spriteBuff = nullptr;
    uint8_t* _lastBuff   = nullptr;
};

#endif