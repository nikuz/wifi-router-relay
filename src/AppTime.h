#ifndef AppTime_h
#define AppTime_h

#include <Arduino.h>

class AppTime {
public:
    AppTime();

    ~AppTime();

    static void config();

    static void printLocalTime();

    static bool isTimeToSleep();

    static bool isTimeBeforeSleep(bool leetcodePassGranted);

    static unsigned long getDelay(bool leetcodePassGranted);
};

#endif /* AppTime_h */