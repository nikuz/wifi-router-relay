#include <Arduino.h>

#include "def.h"
#include "AppTime.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -25200;
const int   daylightOffset_sec = 0;

AppTime::AppTime() {}

AppTime::~AppTime() {}

void printLocalTime() {
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

void AppTime::obtainInternetTime() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
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
    }

    int hourTarget = OFF_HOUR;
    if (leetcodePassGranted) {
        hourTarget += LEETCODE_EXTRA_HOURS;
    }
    
    return timeinfo.tm_hour == hourTarget - 1 && timeinfo.tm_min >= 60 - OFF_NOTIFICATION_MINUTES;
}

