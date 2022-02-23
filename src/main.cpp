#include "config.h"
#include <Arduino.h>
#include "NetworkLogger.h"
#include "CANReader.h"

NetworkLogger networkLogger;
CANReader canReader;

void setup() {
    Serial.begin(115200);
    Serial.println("Setting up");

    networkLogger.setup();
    canReader.setup();

    Serial.println("Ready.");
}

void loop() {
    canReader.loop();
    networkLogger.loop();
}