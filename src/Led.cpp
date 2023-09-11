#include <Arduino.h>
#include <FastLED.h>

#include "def.h"
#include "Led.h"
#include "Relay.h"
#include "AppTime.h"
#include "Leetcode.h"

CRGB leds[LED_AMOUNT];

Led::Led() {}

Led::~Led() {}

void setColor(CRGB::HTMLColorCode color) {
    FastLED.setBrightness(LED_MAX_BRIGHTNESS);
    leds[0] = CRGB::Black;
    FastLED.show();
    FastLED.clear();
    leds[0] = color;
    FastLED.show();
}

void Led::init() {
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<LED_CHIPSET, LED_PIN, LED_COLOR_ORDER>(leds, LED_AMOUNT).setCorrection(TypicalLEDStrip);
}

void Led::control() {
    bool isOn = Relay::isOn();
    bool isLeetcodePassGranted = Leetcode::isPassGranted();
    bool isTimeBeforeSleep = AppTime::isTimeBeforeSleep(isLeetcodePassGranted);

    CRGB::HTMLColorCode onColor = isLeetcodePassGranted ? CRGB::Purple : CRGB::Green;
    CRGB::HTMLColorCode offColor = CRGB::Red;

    if (isTimeBeforeSleep) {
        for (int i = 0; i < 5; i++) {
            setColor(offColor);
            delay(500);
            setColor(onColor);
            delay(500);
        }
    }

    if (isOn && !isLeetcodePassGranted) {
        setColor(offColor);
    } else {
        setColor(onColor);
    }
}
