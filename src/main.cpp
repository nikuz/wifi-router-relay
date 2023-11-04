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
    AppTime::printLocalTime();

    bool isOn = Relay::isOn();
    bool leetcodePassGranted = Leetcode::isPassGranted();

    // request leetcode stats if pass is not granted yet
    if (isOn && !leetcodePassGranted) {
        AppWiFi::connect();
        Leetcode::obtainStats();
        AppWiFi::disconnect();
    }

    // store counter in local storage and reset leetcode pass
    Leetcode::storeCounter(leetcodePassGranted);
    leetcodePassGranted = Leetcode::isPassGranted();

    bool isTimeToSleep = AppTime::isTimeToSleep();
    
    if (isTimeToSleep && isOn && !leetcodePassGranted) {
        Relay::off();
    } else if (!isTimeToSleep && !isOn) {
        Relay::on();
    }

    Led::control(leetcodePassGranted);
    delay(AppTime::getDelay(leetcodePassGranted));
}