#ifndef Relay_h
#define Relay_h

#include <Arduino.h>

class Relay {
public:
    Relay();

    ~Relay();

    static void init();

    static void on();

    static bool isOn();

    static void off();
};

#endif /* Relay_h */