#ifndef _INK_ESPI_H_
#define _INK_ESPI_H_

#include <Arduino.h>
#include <SPI.h>
#include "soc/spi_reg.h"
#include "config.h"
#include "WFT0154CZB3_INIT.h"
#include "fontResource.h"

extern SPIClass ink_spi;

#define SPI_PORT VSPI

#define INK_SPI_FREQUENCY 10000000

#define INK_FULL_MODE    0x00
#define INK_PARTIAL_MODE 0x01

#define INK_CLENR_MODE0 0
#define INK_CLEAR_MODE1 1

#define CS_WRITE_L GPIO.out_w1tc = (1 << INK_SPI_CS)
#define CS_WRITE_H GPIO.out_w1ts = (1 << INK_SPI_CS)

#define DC_WRITE_L GPIO.out_w1tc = (1 << INK_SPI_DC)
#define DC_WRITE_H GPIO.out_w1ts = (1 << INK_SPI_DC)

#define RST_WRITE_L GPIO.out_w1tc = (1 << INK_SPI_RST)
#define RST_WRITE_H GPIO.out_w1ts = (1 << INK_SPI_RST)

#define INK_WRITE_8(C)                                     \
    WRITE_PERI_REG(SPI_MOSI_DLEN_REG(SPI_PORT), 8 - 1);    \
    WRITE_PERI_REG(SPI_W0_REG(SPI_PORT), C);               \
    SET_PERI_REG_MASK(SPI_CMD_REG(SPI_PORT), SPI_USR);     \
    while (READ_PERI_REG(SPI_CMD_REG(SPI_PORT)) & SPI_USR) \
        ;

// Write 16 bits with corrected endianess for 16 bit colours
#define INK_WRITE_16(C)                                    \
    WRITE_PERI_REG(SPI_MOSI_DLEN_REG(SPI_PORT), 16 - 1);   \
    WRITE_PERI_REG(SPI_W0_REG(SPI_PORT), C << 8 | C >> 8); \
    SET_PERI_REG_MASK(SPI_CMD_REG(SPI_PORT), SPI_USR);     \
    while (READ_PERI_REG(SPI_CMD_REG(SPI_PORT)) & SPI_USR) \
        ;

// Write 16 bits
#define INK_WRITE_16S(C)                                   \
    WRITE_PERI_REG(SPI_MOSI_DLEN_REG(SPI_PORT), 16 - 1);   \
    WRITE_PERI_REG(SPI_W0_REG(SPI_PORT), C);               \
    SET_PERI_REG_MASK(SPI_CMD_REG(SPI_PORT), SPI_USR);     \
    while (READ_PERI_REG(SPI_CMD_REG(SPI_PORT)) & SPI_USR) \
        ;

// Write 32 bits
#define INK_WRITE_32(C)                                    \
    WRITE_PERI_REG(SPI_MOSI_DLEN_REG(SPI_PORT), 32 - 1);   \
    WRITE_PERI_REG(SPI_W0_REG(SPI_PORT), C);               \
    SET_PERI_REG_MASK(SPI_CMD_REG(SPI_PORT), SPI_USR);     \
    while (READ_PERI_REG(SPI_CMD_REG(SPI_PORT)) & SPI_USR) \
        ;

class Ink_eSPI {
   public:
    Ink_eSPI(uint16_t width = 200, uint16_t height = 200);

    ~Ink_eSPI();

    void begin();

    int32_t width() {
        return _width;
    }
    int32_t height() {
        return _height;
    }

    bool isBusy();
    bool isInit();

    int writeInitList(const unsigned char* list);
    int clear(int mode = INK_CLENR_MODE0);
    int clearDSRAM();
    int drawBuff(uint8_t* buff, bool bitMode = true);
    int drawBuff(uint8_t* lastbuff, uint8_t* buff, size_t size);

    void switchMode(int mode);
    int getMode() {
        return _mode;
    }

    void setDrawAddr(uint16_t posx, uint16_t posy, uint16_t width,
                     uint16_t height);
    uint8_t getPix(uint16_t posX, uint16_t posY);

    void deepSleep();
    void powerHVON();
    void powerHVOFF();

   private:
    int writeCMD(uint8_t cmd);
    int writeData(uint8_t data);
    int waitbusy(uint16_t time);

   private:
    bool _isInit = false;
    int32_t _width, _height;
    int32_t _pixsize;

    int _mode = INK_FULL_MODE;

    uint8_t* _lastbuff = nullptr;
};

#endif