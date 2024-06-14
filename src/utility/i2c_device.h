#ifndef _I2C_DEVICE_BUS_
#define _I2C_DEVICE_BUS_

#include "Arduino.h"
#include "Wire.h"

class I2C_DEVICE {
   private:
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _freq;

   public:
    void begin(TwoWire* wire, uint8_t sda, uint8_t scl, long freq = 100000);
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    bool writeByte(uint8_t addr, uint8_t reg, uint8_t data);
    uint8_t readByte(uint8_t addr, uint8_t reg);
    bool writeBitOn(uint8_t addr, uint8_t reg, uint8_t data);
    bool writeBitOff(uint8_t addr, uint8_t reg, uint8_t data);
};

#endif