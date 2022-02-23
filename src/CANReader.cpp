//
// Created by samuel on 23-02-22.
//

#include "CANReader.h"

CANBuffer canBuffer;

void CANReader::setup() {
    Serial.print("Initializing CAN... ");

    // Initialize MCP2515 running at 8MHz with a baudrate of 500kb/s and the masks and filters disabled.
    while (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK) {
        Serial.println("Error Initializing MCP2515...");
        delay(2000);
    }

    Serial.println("MCP2515 Initialized Successfully!");

    CAN0.setMode(MCP_LISTENONLY);
    pinMode(CAN0_INT, INPUT);
}

void CANReader::loop() {
    if (!messageAvailable()) {
        return;
    }

    CAN_Message message = readMessage();
    canBuffer.push(message);
}

bool CANReader::messageAvailable() {
    // If CAN0_INT pin is low, read receive buffer
    return !digitalRead(CAN0_INT);
}

CAN_Message CANReader::readMessage() {
    unsigned long rxId;
    uint8_t len = 0;
    uint8_t rxBuf[8];

    // Read data: len = data length, buf = data byte(s)
    CAN0.readMsgBuf(&rxId, &len, rxBuf);
    CAN_Message message = CAN_Message(millis(), rxId, len, rxBuf);
    return message;
}
