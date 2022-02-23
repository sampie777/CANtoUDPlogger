//
// Created by samuel on 23-02-22.
//

#ifndef CANTOUDPLOGGER_CANBUFFER_H
#define CANTOUDPLOGGER_CANBUFFER_H

#include "config.h"
#include <Arduino.h>
#include "CAN_Message.h"

class CANBuffer {
public:
    void push(CAN_Message message);
    bool isUnique(CAN_Message message);
    uint8_t unreadCount();
    uint8_t getAddIndex() { return addIndex; }
    uint8_t getReadIndex() { return readIndex; }
    CAN_Message pop();

private:
    CAN_Message buffer[BUFFER_SIZE];
    uint8_t addIndex = 0;
    uint8_t readIndex = 0;
};

extern CANBuffer canBuffer;


#endif //CANTOUDPLOGGER_CANBUFFER_H
