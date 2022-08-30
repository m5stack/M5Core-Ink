#include "Ink_eSPI.h"

SPIClass ink_spi = SPIClass(VSPI);

Ink_eSPI::Ink_eSPI(uint16_t width, uint16_t height) {
    _width   = width;
    _height  = height;
    _pixsize = _width * _height / 8;

    _lastbuff = (uint8_t *)malloc(sizeof(uint8_t) * _pixsize);
    if (_lastbuff != nullptr) {
        memset(_lastbuff, 0xff, sizeof(uint8_t) * _pixsize);
    }
}

Ink_eSPI::~Ink_eSPI() {
    if (_lastbuff != nullptr) free(_lastbuff);
}

void Ink_eSPI::begin() {
    pinMode(INK_SPI_CS, OUTPUT);
    pinMode(INK_SPI_DC, OUTPUT);
    pinMode(INK_SPI_RST, OUTPUT);
    pinMode(INK_SPI_BUSY, INPUT);

    digitalWrite(INK_SPI_CS, HIGH);
    digitalWrite(INK_SPI_DC, HIGH);
    digitalWrite(INK_SPI_RST, HIGH);

    ink_spi.begin(INK_SPI_SCK, -1, INK_SPI_MOSI, -1);

    RST_WRITE_H;
    delay(10);
    RST_WRITE_L;
    delay(100);
    RST_WRITE_H;
    delay(100);

    int initTime = waitbusy(1000);

    writeInitList(WFT0154CZB3_LIST);

    delay(100);

    initTime = waitbusy(1000);

    _isInit = (initTime > 0) ? true : false;

    if (_lastbuff == nullptr) {
        _isInit = false;
    }
}

int Ink_eSPI::writeCMD(uint8_t cmd) {
    ink_spi.beginTransaction(
        SPISettings(INK_SPI_FREQUENCY, MSBFIRST, SPI_MODE3));
    CS_WRITE_L;
    DC_WRITE_L;
    INK_WRITE_8(cmd);
    CS_WRITE_H;
    ink_spi.endTransaction();
    return 0;
}
int Ink_eSPI::writeData(uint8_t data) {
    ink_spi.beginTransaction(
        SPISettings(INK_SPI_FREQUENCY, MSBFIRST, SPI_MODE3));
    CS_WRITE_L;
    DC_WRITE_H;
    INK_WRITE_8(data);
    CS_WRITE_H;
    ink_spi.endTransaction();
    return 0;
}

bool Ink_eSPI::isBusy() {
    return (digitalRead(INK_SPI_BUSY) == HIGH) ? false : true;
}
int Ink_eSPI::waitbusy(uint16_t time) {
    while ((isBusy() == true) && (time > 0)) {
        time--;
        delay(1);
    }
    return time;
}

int Ink_eSPI::writeInitList(const unsigned char *list) {
    int listLimit           = list[0];
    unsigned char *startPtr = ((unsigned char *)list + 1);
    for (int i = 0; i < listLimit; i++) {
        writeCMD(*(startPtr + 0));

        for (int dnum = 0; dnum < *(startPtr + 1); dnum++) {
            writeData(*(startPtr + 2 + dnum));
        }
        startPtr += (*(startPtr + 1) + 2);
    }
    return 0;
}

int Ink_eSPI::clear(int mode) {
    if (!isInit()) return -1;

    if (mode == 0) {
        writeCMD(0x10);
        for (int count = 0; count < _pixsize; count++) {
            writeData(0xff);
        }
        delay(2);
        writeCMD(0x13);
        for (int count = 0; count < _pixsize; count++) {
            writeData(0x00);
        }
        delay(2);
        writeCMD(0x12);
        waitbusy(1000);

        writeCMD(0x10);
        for (int count = 0; count < _pixsize; count++) {
            writeData(0x00);
        }
        delay(2);
        writeCMD(0x13);
        for (int count = 0; count < _pixsize; count++) {
            writeData(0xff);
        }
        delay(2);
        writeCMD(0x12);
        waitbusy(1000);
    } else if (mode == 1) {
        writeCMD(0x10);
        for (int count = 0; count < _pixsize; count++) {
            writeData(_lastbuff[count]);
        }
        delay(2);
        writeCMD(0x13);
        for (int count = 0; count < _pixsize; count++) {
            writeData(0xff);
        }
        delay(2);
        writeCMD(0x12);
        waitbusy(1000);
    }

    return 0;
}

int Ink_eSPI::clearDSRAM() {
    if (!isInit()) return -1;

    for (int i = 0; i < 2; i++) {
        writeCMD(0x10);
        for (int count = 0; count < _pixsize; count++) {
            writeData(0x00);
        }
        delay(2);
        writeCMD(0x13);
        for (int count = 0; count < _pixsize; count++) {
            writeData(0xff);
        }
    }
    return 0;
}
int Ink_eSPI::drawBuff(uint8_t *buff, bool bitMode) {
    if (!isInit()) return -1;

    if (_mode != INK_FULL_MODE) {
        switchMode(INK_FULL_MODE);
    }

    writeCMD(0x10);
    for (int i = 0; i < _pixsize; i++) {
        writeData(_lastbuff[i]);
    }
    delay(2);
    writeCMD(0x13);
    for (int i = 0; i < _pixsize; i++) {
        writeData((bitMode) ? buff[i] : ~buff[i]);
        _lastbuff[i] = (bitMode) ? buff[i] : ~buff[i];
    }
    delay(2);
    writeCMD(0x12);
    return waitbusy(1000);
}

int Ink_eSPI::drawBuff(uint8_t *lastbuff, uint8_t *buff, size_t size) {
    if (!isInit()) return -1;

    writeCMD(0x10);
    for (int i = 0; i < size; i++) {
        writeData(lastbuff[i]);
    }
    writeCMD(0x13);
    for (int i = 0; i < size; i++) {
        writeData(buff[i]);
        lastbuff[i] = buff[i];
    }
    writeCMD(0x12);
    delay(100);
    return waitbusy(1000);
}

bool Ink_eSPI::isInit() {
    return _isInit;
}

void Ink_eSPI::switchMode(int mode) {
    if (mode == INK_PARTIAL_MODE) {
        if (_mode == INK_FULL_MODE) {
            begin();
        }
        writeCMD(0x00);  // panel setting
        writeData(0xff);
        writeData(0x0e);

        int count = 0;
        writeCMD(0x20);
        for (count = 0; count < 42; count++) {
            writeData(pgm_read_byte(&lut_vcomDC1[count]));
        }

        writeCMD(0x21);
        for (count = 0; count < 42; count++) {
            writeData(pgm_read_byte(&lut_ww1[count]));
        }

        writeCMD(0x22);
        for (count = 0; count < 42; count++) {
            writeData(pgm_read_byte(&lut_bw1[count]));
        }

        writeCMD(0x23);
        for (count = 0; count < 42; count++) {
            writeData(pgm_read_byte(&lut_wb1[count]));
        }

        writeCMD(0x24);
        for (count = 0; count < 42; count++) {
            writeData(pgm_read_byte(&lut_bb1[count]));
        }
        _mode = INK_PARTIAL_MODE;
        Serial.printf("Switch Mode to INK_PARTIAL_MODE \r\n");
    } else {
        begin();
        // writeCMD(0x00); //panel setting
        // writeData(0xDf);
        // writeData(0x0e);

        _mode = INK_FULL_MODE;
        Serial.printf("Switch Mode to INK_FULL_MODE \r\n");
    }
}

void Ink_eSPI::setDrawAddr(uint16_t posx, uint16_t posy, uint16_t width,
                           uint16_t height) {
    writeCMD(0x91);   // This command makes the display enter partial mode
    writeCMD(0x90);   // resolution setting
    writeData(posx);  // x-start
    writeData(posx + width - 1);  // x-end
    writeData(0);                 // x Reserved

    writeData(posy);           // y-start
    writeData(0);              // y Reserved
    writeData(posy + height);  // y-end
    writeData(0x01);
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
    writeCMD(0X50);
    writeData(0xf7);
    writeCMD(0X02);  // power off
    waitbusy(5000);
    writeCMD(0X07);  // deep sleep
    writeData(0xA5);
}

void Ink_eSPI::powerHVON() {
    writeCMD(0X50);
    writeData(0xd7);
    writeCMD(0X04);
    waitbusy(5000);
}

void Ink_eSPI::powerHVOFF() {
    writeCMD(0X50);
    writeData(0xf7);
    writeCMD(0X02);
    waitbusy(5000);
}