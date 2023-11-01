#include "def.h"
#include "AppWiFi.h"
#include "AppTime.h"
#include "Leetcode.h"
#include "Led.h"
#include "Relay.h"

void setup() {
    Serial.begin(SERIAL_BAUD);

    Relay::init();
    Relay::on();

    Led::init();

    AppWiFi::connect();
    AppTime::config();
    AppWiFi::disconnect();
}

void loop() {
    bool isOn = Relay::isOn();
    bool isLeetcodePassGranted = Leetcode::isPassGranted();

    AppTime::printLocalTime();

    if (isOn && !isLeetcodePassGranted) {
        AppWiFi::connect();
        Leetcode::obtainStats();
        AppWiFi::disconnect();
    }

    bool isTimeToSleep = AppTime::isTimeToSleep();
    
    if (isTimeToSleep && isOn && !isLeetcodePassGranted) {
        Relay::off();
    } else if (!isTimeToSleep && !isOn) {
        Relay::on();
    }

    Led::control();
    Leetcode::storeCounter(isLeetcodePassGranted);

    delay(AppTime::getDelay(isLeetcodePassGranted));
}