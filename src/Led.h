#ifndef Led_h
#define Led_h

#include <Arduino.h>

class Led {
public:
    Led();

    ~Led();

    static void init();

    static void control(bool leetcodePassGranted);
};

#endif /* Led_h */