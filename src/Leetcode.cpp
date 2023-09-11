#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
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

    String requestUrl = "http://leetcode-stats-api.herokuapp.com/" + String(LEETCODE_USER);

    WiFiClient client;
    HTTPClient http;
        
    http.begin(client, requestUrl);

    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
        String payload = http.getString();
        JSONVar response = JSON.parse(payload);

        if (JSON.typeof(response) == "undefined") {
            Serial.println("Leetcode: Parsing input failed!");
            return;
        }

        if (String(response["status"]) != "success") {
            Serial.println("Leetcode: Failed to retrieve stats");
            return;
        }

        int counter = int(response["totalSolved"]);
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
