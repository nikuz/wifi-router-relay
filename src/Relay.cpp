#include <Arduino.h>

#include "def.h"
#include "Relay.h"

bool _isOn = true;

Relay::Relay() {}

Relay::~Relay() {}

void Relay::init() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, 0);

    Serial.print("off at: ");
    Serial.println(OFF_HOUR);
    Serial.print("on at: ");
    Serial.println(ON_HOUR);
}

void Relay::on() {
    _isOn = true;
    digitalWrite(RELAY_PIN, 0);

    Serial.println("on");
}

bool Relay::isOn() {
    return _isOn;
}

void Relay::off() {
    _isOn = false;
    digitalWrite(RELAY_PIN, 1);
    
    Serial.println("off");
}