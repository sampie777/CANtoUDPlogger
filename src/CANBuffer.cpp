//
// Created by samuel on 23-02-22.
//

#include "CANBuffer.h"

void CANBuffer::push(CAN_Message message) {
    if (!isUnique(message)) {
        return;
    }

    if (addIndex >= BUFFER_SIZE) {
        addIndex = 0;
    }

    CAN_Message newMessage = CAN_Message(message.timestamp, message.id, message.len, message.rxBuf);
    buffer[addIndex++] = newMessage;
}

bool CANBuffer::isUnique(CAN_Message message) {
    return true;
}

uint8_t CANBuffer::unreadCount() {
    if (readIndex > addIndex) {
        return BUFFER_SIZE - 1 - readIndex + addIndex;
    }
    return addIndex - readIndex;
}

CAN_Message CANBuffer::pop() {
    CAN_Message message = buffer[readIndex++];

    if (readIndex >= BUFFER_SIZE) {
        readIndex = 0;
    }

    return CAN_Message(message.timestamp, message.id, message.len, message.rxBuf);
}
