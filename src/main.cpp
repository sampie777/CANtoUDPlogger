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
#if !OFFLINE
    canReader.setup();
#endif

    Serial.println("Ready.");
}

void loop() {
#if OFFLINE
    static unsigned long lastTime = 0;
    if (millis() > lastTime + 120) {
        lastTime = millis();
        uint8_t buffer[8] = {0};
        buffer[0] = 3;
        buffer[1] = 4;
        canBuffer.push(CAN_Message(millis(), rand(), 1, buffer));
    }
#endif

#if !OFFLINE
    canReader.loop();
#endif
    networkLogger.loop();
}