#ifndef Leetcode_h
#define Leetcode_h

#include <Arduino.h>

class Leetcode {
public:
    Leetcode();

    ~Leetcode();

    static void obtainStats();

    static void storeCounterIfAbsent(int counter);
    
    static void storeCounter(bool isPassGranted);

    static bool isPassGranted();
};

#endif /* Leetcode_h */