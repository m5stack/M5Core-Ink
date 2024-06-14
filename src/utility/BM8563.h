#ifndef __BM8563_H__
#define __BM8563_H__

#include <Wire.h>
#include "i2c_device.h"

#define BM8563_I2C_ADDR 0x51

typedef struct RTC_Time {
    int8_t Hours;
    int8_t Minutes;
    int8_t Seconds;
    bool VLFlag;
    RTC_Time() : Hours(), Minutes(), Seconds() {
    }
    RTC_Time(int8_t h, int8_t m, int8_t s) : Hours(h), Minutes(m), Seconds(s) {
    }
} RTC_TimeTypeDef;

typedef struct RTC_Date {
    int8_t WeekDay;
    int8_t Month;
    int8_t Date;
    int16_t Year;
    RTC_Date() : WeekDay(), Month(), Date(), Year() {
    }
    RTC_Date(int8_t w, int8_t m, int8_t d, int16_t y)
        : WeekDay(w), Month(m), Date(d), Year(y) {
    }
} RTC_DateTypeDef;

class RTC {
   public:
    RTC();

    void begin(void);

    void GetBm8563Time(void);

    void SetTime(RTC_TimeTypeDef *RTC_TimeStruct);
    void SetDate(RTC_DateTypeDef *RTC_DateStruct);

    void GetTime(RTC_TimeTypeDef *RTC_TimeStruct);
    void GetDate(RTC_DateTypeDef *RTC_DateStruct);

    int SetAlarmIRQ(int afterSeconds);
    int SetAlarmIRQ(const RTC_TimeTypeDef &RTC_TimeStruct);
    int SetAlarmIRQ(const RTC_DateTypeDef &RTC_DateStruct,
                    const RTC_TimeTypeDef &RTC_TimeStruct);

    void clearIRQ();
    void disableIRQ();

   public:
    uint8_t Second;
    uint8_t Minute;
    uint8_t Hour;
    uint8_t Week;
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;
    uint8_t DateString[9];
    uint8_t TimeString[9];

    uint8_t asc[14];

   private:
    void Bcd2asc(void);
    void DataMask();
    void Str2Time(void);

    uint8_t bcd2ToByte(uint8_t value);
    uint8_t byteToBcd2(uint8_t value);

    I2C_DEVICE _i2c;

   private:
    /*定义数组用来存储读取的时间数据 */
    uint8_t trdata[7];
    /*定义数组用来存储转换的 asc 码时间数据*/
    // uint8_t asc[14];
};

#endif
