#ifndef AppTime_h
#define AppTime_h

#include <Arduino.h>

class AppTime {
public:
    AppTime();

    ~AppTime();

    static void obtainInternetTime();

    static bool isTimeToSleep();

    static bool isTimeBeforeSleep(bool leetcodePassGranted);
};

#endif /* AppTime_h */