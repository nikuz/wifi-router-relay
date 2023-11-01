#include <Arduino.h>

#include "def.h"
#include "AppTime.h"

AppTime::AppTime() {}

AppTime::~AppTime() {}

void AppTime::config() {
    configTime(0, 0, NTP_SERVER);
    setenv("TZ", TIMEZONE, 1);
    tzset();

    struct tm timeinfo;
    getLocalTime(&timeinfo);
}

void AppTime::printLocalTime() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.print(timeinfo.tm_hour);
    Serial.print(":");
    Serial.print(timeinfo.tm_min);
    Serial.print(":");
    Serial.println(timeinfo.tm_sec);
}

bool AppTime::isTimeToSleep() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return false;
    }
    
    return timeinfo.tm_hour >= OFF_HOUR || timeinfo.tm_hour < ON_HOUR;
}

bool AppTime::isTimeBeforeSleep(bool leetcodePassGranted) {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return false;
    }

    int hourTarget = OFF_HOUR;
    if (leetcodePassGranted) {
        hourTarget += LEETCODE_EXTRA_HOURS;
    }
    
    return timeinfo.tm_hour == hourTarget - 1 && timeinfo.tm_min >= 60 - OFF_NOTIFICATION_MINUTES;
}

unsigned long AppTime::getDelay(bool leetcodePassGranted) {
    unsigned long oneMinuteDelay = 1000 * 60;
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return oneMinuteDelay;
    }

    int hourTarget = OFF_HOUR;
    if (leetcodePassGranted) {
        hourTarget += LEETCODE_EXTRA_HOURS;
    }

    bool lastHour = timeinfo.tm_hour == hourTarget - 1;
    if (lastHour) {
        return oneMinuteDelay;
    }

    int minutes = (60 - timeinfo.tm_min) * 60 * 1000;
    int seconds = (60 - timeinfo.tm_sec) * 1000;

    return minutes + seconds + 1000;
}

