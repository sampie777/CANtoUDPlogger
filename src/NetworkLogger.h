//
// Created by samuel on 23-02-22.
//

#ifndef CANTOUDPLOGGER_NETWORKLOGGER_H
#define CANTOUDPLOGGER_NETWORKLOGGER_H

#include "config.h"
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include "CANBuffer.h"

class NetworkLogger {
public:
    void setup();
    void ping();
    void loop();

private:
    AsyncUDP udp;
    void processReceivedPacket(AsyncUDPPacket packet);
};

extern NetworkLogger networkLogger;

#endif //CANTOUDPLOGGER_NETWORKLOGGER_H
