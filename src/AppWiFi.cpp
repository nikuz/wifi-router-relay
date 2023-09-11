#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "def.h"
#include "WiFiClient.h"
#include "AppWiFi.h"
#include "AppWiFiDef.h"

AppWiFi::AppWiFi() {}

AppWiFi::~AppWiFi() {}


void AppWiFi::connect() {
    Serial.printf("Connecting to %s ", WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("WiFi Connected");
}

void AppWiFi::disconnect() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi Disconnected");
}
