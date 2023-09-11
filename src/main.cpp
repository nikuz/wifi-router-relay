#include "def.h"
#include "AppWiFi.h"
#include "AppTime.h"
#include "Leetcode.h"
#include "Led.h"
#include "Relay.h"

unsigned long delayInterval = 1000 * 60; // one minute

void setup() {
    Serial.begin(SERIAL_BAUD);

    Relay::init();
    Relay::on();

    Led::init();
}

void loop() {
    bool isOn = Relay::isOn();

    if (isOn) {
        AppWiFi::connect();
        AppTime::obtainInternetTime();
        Leetcode::obtainStats();
        AppWiFi::disconnect();
    }

    bool isTimeToSleep = AppTime::isTimeToSleep();
    bool isLeetcodePassGranted = Leetcode::isPassGranted();
    
    if (isTimeToSleep && isOn && !isLeetcodePassGranted) {
        Relay::off();
    } else if (!isTimeToSleep && !isOn) {
        Relay::on();
    }

    Led::control();
    Leetcode::storeCounter(isLeetcodePassGranted);

    delay(delayInterval);
}