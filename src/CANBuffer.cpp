//
// Created by samuel on 23-02-22.
//

#include "CANBuffer.h"

void CANBuffer::push(CAN_Message message) {
    if (!isUnique(message)) {
        return;
    }

    CAN_Message newMessage = CAN_Message(message.timestamp, message.id, message.len, message.rxBuf);
    buffer[addIndex++] = newMessage;

    if (addIndex >= BUFFER_SIZE) {
        addIndex = 0;
    }
}

bool CANBuffer::isUnique(CAN_Message message) {
    // Get last message ID index
    int lastMessageIndex = -1;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        int j = addIndex - 1 - i;
        while (j < 0) {
            j += BUFFER_SIZE;
        }

        if (buffer[j].id == message.id) {
            lastMessageIndex = j;
            break;
        }
    }

    if (lastMessageIndex < 0) {
        return true;
    }

    // Compare last message with new message
    if (message.len != buffer[lastMessageIndex].len) {
        return true;
    }

    for (uint8_t i = 0; i < message.len; i++) {
        if (message.rxBuf[i] != buffer[lastMessageIndex].rxBuf[i]) {
            return true;
        }
    }
    return false;
}

uint8_t CANBuffer::unreadCount() {
    if (readIndex > addIndex) {
        return BUFFER_SIZE - readIndex + addIndex;
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
