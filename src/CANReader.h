//
// Created by samuel on 23-02-22.
//

#ifndef CANTOUDPLOGGER_CANREADER_H
#define CANTOUDPLOGGER_CANREADER_H

#include "config.h"
#include <Arduino.h>
#include "../lib/MCP_CAN_lib-master/mcp_can.h"
#include "CAN_Message.h"
#include "CANBuffer.h"


class CANReader {
public:
    CANReader() : CAN0(CAN0_CS) {}

    void setup();
    void loop();
    bool messageAvailable();
    CAN_Message readMessage();

private:
    MCP_CAN CAN0;
};

extern CANReader canReader;

#endif //CANTOUDPLOGGER_CANREADER_H
