// This RTC clock example keeps the system mostly in shutdown mode and
//  only wakes up every 58 seconds for a brief period of time during
//  which the time and date are updated on the ink display.
//
// When started initially or via power button a full ink display refresh
//  is executed to clear the display.
// The current time and date are fetched via NTP and shown on the ink display.
// After waiting for the full minute the system is put into shutdown
//  mode for about 58 seconds.
// When the RTC timer expires (just befor the next minute change) the
//  system is powered on.
// The ink display is updated with the current time and date.
// Then the system goes back into shutdown mode for about 58 seconds and
//  the cycle begins anew.
// Every hour a full ink display refresh is executed to keep the ink
//  display crisp.
//
// Note: If WiFi connection fails - some fantasy time and date are used.
// Note: System will not enter shutdown mode while USB is connected.

#include "M5CoreInk.h"
#include <WiFi.h>
#include "time.h"

const char* ssid             = "YOUR_SSID";
const char* password         = "YOUR_PASSWORD";
const char* ntpServer        = "pool.ntp.org";
const long gmtOffset_sec     = 3600;
const int daylightOffset_sec = 3600;

// every hour at minute 45 do a full ink display refresh
#define FULL_REFRESH_MINUTE (45)

Ink_Sprite TimePageSprite(&M5.M5Ink);

void printLocalTimeAndSetRTC()
{
    struct tm timeinfo;

    if(getLocalTime(&timeinfo) == false)
    {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    RTC_TimeTypeDef time;
    time.Hours = timeinfo.tm_hour;
    time.Minutes = timeinfo.tm_min;
    time.Seconds = timeinfo.tm_sec;
    M5.rtc.SetTime(&time);

    RTC_DateTypeDef date;
    date.Date = timeinfo.tm_mday;
    date.Month = timeinfo.tm_mon + 1;
    date.Year = timeinfo.tm_year + 1900;
    M5.rtc.SetDate(&date);
}

void getNTPTime()
{
    // Try to connect for 10 seconds
    uint32_t connect_timeout = millis() + 10000;

    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while((WiFi.status() != WL_CONNECTED) && (millis() < connect_timeout))
    {
        delay(500);
        Serial.print(".");
    }
    if(WiFi.status() != WL_CONNECTED)
    {
        // WiFi connection failed - set fantasy time and date
        RTC_TimeTypeDef time;
        time.Hours = 6;
        time.Minutes = 43;
        time.Seconds = 50;
        M5.rtc.SetTime(&time);

        RTC_DateTypeDef date;
        date.Date = 4;
        date.Month = 12;
        date.Year = 2020;
        M5.rtc.SetDate(&date);
        return;
    }

    Serial.println("Connected");

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTimeAndSetRTC();

    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}

void drawTimeAndDate(RTC_TimeTypeDef time, RTC_DateTypeDef date)
{
    char buf[11];

    snprintf(buf, 6, "%02d:%02d", time.Hours, time.Minutes);
    TimePageSprite.drawString(40, 20, buf, &AsciiFont24x48);
    snprintf(buf, 11, "%02d.%02d.%02d", date.Date, date.Month, date.Year - 2000);
    TimePageSprite.drawString(4, 70, buf, &AsciiFont24x48);
}

void setup()
{
    // Check power on reason before calling M5.begin()
    //  which calls Rtc.begin() which clears the timer flag.
    Wire1.begin(21, 22);
    uint8_t data = M5.rtc.ReadReg(0x01);

    M5.begin();
    // Green LED - indicates ESP32 is running
    digitalWrite(LED_EXT_PIN, LOW);

    if(M5.M5Ink.isInit() == false)
    {
        Serial.printf("Ink Init failed");
        while(1) delay(100);
    }

    RTC_TimeTypeDef time;
    RTC_DateTypeDef date;

    // Check timer flag
    if((data & 0b00000100) == 0b00000100)
    {
        Serial.println("Power on by: RTC timer");
        M5.rtc.GetTime(&time);
        M5.rtc.GetDate(&date);
        // Full refresh once per hour
        if(time.Minutes == FULL_REFRESH_MINUTE - 1)
        {
          M5.M5Ink.clear();
        }
    }
    else
    {
        Serial.println("Power on by: power button");
        M5.M5Ink.clear();
        // Fetch current time from Internet
        getNTPTime();
        M5.rtc.GetTime(&time);
        M5.rtc.GetDate(&date);
    }

    // After every shutdown the sprite is created anew.
    // But the sprite doesn't know about the current image on the
    //  ink display therefore the same time and date, as have been
    //  drawn before the shutdown, are redrawn.
    // This is required, else drawing new time and date only adds
    //  pixels to the already drawn pixels instead of clearing the
    //  previous time and date and then draw the new time and date.
    TimePageSprite.creatSprite(0, 0, 200, 200);

    drawTimeAndDate(time, date);
    TimePageSprite.pushSprite();

    // Wait until full minute, e.g. seconds are 0
    while((time.Seconds != 0))
    {
        M5.rtc.GetTime(&time);
        delay(200);
    }
    M5.rtc.GetDate(&date);

    // Draw new time and date
    drawTimeAndDate(time, date);
    TimePageSprite.pushSprite();

    Serial.printf("Shutdown...\n");
    Serial.flush();

    // Full refresh once per hour
    if(time.Minutes == FULL_REFRESH_MINUTE - 1)
    {
        // Allow extra time for full ink refresh
        // Shutdown for 55 seconds only
        M5.shutdown(55);
        return;
    }
    // Shutdown for 58 seconds
    M5.shutdown(58);
}

void loop()
{

}
