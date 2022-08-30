#ifndef _FONTRESOURCE_H_
#define _FONTRESOURCE_H_

#include <Arduino.h>

typedef struct Ink_eSPI_font {
    uint16_t _width;
    uint16_t _height;
    uint16_t _fontSize;
    const uint8_t* _fontptr;
    Ink_eSPI_font(int width, int height, const uint8_t* ptr) {
        _width   = width;
        _height  = height;
        _fontptr = ptr;

        _fontSize = _width * _height / 8;
    }
} Ink_eSPI_font_t;

extern const unsigned char FontLib8x16[];
extern const unsigned char FontLib24x48[];

extern Ink_eSPI_font_t AsciiFont8x16;
extern Ink_eSPI_font_t AsciiFont24x48;

#endif