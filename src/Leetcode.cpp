#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Preferences.h>

#include "def.h"
#include "Leetcode.h"

Preferences preferences;
int leetcodeCounter = 0;
const char* preferencesScope = "leetcode"; 
const char* preferencesName = "leetcode-tasks"; 

Leetcode::Leetcode() {}

Leetcode::~Leetcode() {}


void Leetcode::obtainStats() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Leetcode: WiFi is not connected");
        return;
    }

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setInsecure();
    HTTPClient http;
        
    http.begin(*client, LEETCODE_SYNC_URL);

    int httpResponseCode = http.GET();
    Serial.print("Response code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println(payload);

        int counter = payload.toInt();
        Serial.print("Leetcode: ");
        Serial.println(counter);
        Leetcode::storeCounterIfAbsent(counter);
    }

    http.end();
}

void Leetcode::storeCounterIfAbsent(int counter) {
    leetcodeCounter = counter;
    preferences.begin(preferencesScope, false);
    int storedCounter = preferences.getInt(preferencesName, 0);
    if (storedCounter == 0) {
        preferences.putInt(preferencesName, counter);
    }
    preferences.end();
}

bool Leetcode::isPassGranted() {
    preferences.begin(preferencesScope, false);
    int counter = preferences.getInt(preferencesName, 0);
    preferences.end();

    return counter < leetcodeCounter;
}

void Leetcode::storeCounter(bool isPassGranted) {
    if (!isPassGranted) {
        return;
    }

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return;
    }

    if (timeinfo.tm_hour == OFF_HOUR + LEETCODE_EXTRA_HOURS) {
        preferences.begin(preferencesScope, false);
        preferences.putInt(preferencesName, leetcodeCounter);
        preferences.end();
    }
}
