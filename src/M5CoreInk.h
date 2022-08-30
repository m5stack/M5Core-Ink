#ifndef _M5COREINK_H_
#define _M5COREINK_H_

#include <Arduino.h>

#include "utility/config.h"

#include "utility/BM8563.h"
#include "utility/Ink_Sprite.h"
#include "utility/Button.h"
#include "utility/Ink_eSPI.h"
#include "utility/Ink_Sprite.h"
#include "utility/Speaker.h"

class M5CoreInk {
   private:
    /* data */
    // WFT0154CZB3
   public:
    M5CoreInk(/* args */);
    ~M5CoreInk();

    int begin(bool InkEnable = true, bool wireEnable = false,
              bool SpeakerEnable = false);
    void update();

    void shutdown();
    int shutdown(int seconds);
    int shutdown(const RTC_TimeTypeDef &RTC_TimeStruct);
    int shutdown(const RTC_DateTypeDef &RTC_DateStruct,
                 const RTC_TimeTypeDef &RTC_TimeStruct);

#define DEBOUNCE_MS 10
    Button BtnUP   = Button(BUTTON_UP_PIN, true, DEBOUNCE_MS);
    Button BtnDOWN = Button(BUTTON_DOWN_PIN, true, DEBOUNCE_MS);
    Button BtnMID  = Button(BUTTON_MID_PIN, true, DEBOUNCE_MS);
    Button BtnEXT  = Button(BUTTON_EXT_PIN, true, DEBOUNCE_MS);
    Button BtnPWR  = Button(BUTTON_PWR_PIN, true, DEBOUNCE_MS);

    SPEAKER Speaker;
    RTC rtc;
    Ink_eSPI M5Ink;
};

extern M5CoreInk M5;
#define Rtc rtc
#endif