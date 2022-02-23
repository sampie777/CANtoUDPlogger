//
// Created by samuel on 23-02-22.
//

#include "NetworkLogger.h"

void NetworkLogger::setup() {
    WiFi.enableAP(true);
    bool apStarted = WiFi.softAP(WIFI_SSID, WIFI_PASSWORD, 1, 0, 8);
    if (!apStarted) {
        Serial.println("Failed to setup AP");
    }

    IPAddress ip = WiFi.softAPIP();
    Serial.print("AP IP: ");
    Serial.println(ip);

    if (udp.listen(UDP_PORT)) {
        udp.onPacket([](AsyncUDPPacket packet) {
            networkLogger.processReceivedPacket(packet);
        });
    }
}

void NetworkLogger::ping() {
    udp.broadcast("Ping!");
}

void NetworkLogger::processReceivedPacket(AsyncUDPPacket packet) {
    Serial.print("UDP Packet Type: ");
    Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
    Serial.print(", From: ");
    Serial.print(packet.remoteIP());
    Serial.print(":");
    Serial.print(packet.remotePort());
    Serial.print(", To: ");
    Serial.print(packet.localIP());
    Serial.print(":");
    Serial.print(packet.localPort());
    Serial.print(", Length: ");
    Serial.print(packet.length());
    Serial.print(", Data: ");
    Serial.write(packet.data(), packet.length());
    Serial.println();
    String myString = (const char *) packet.data();
    packet.printf("Got %u bytes of data", packet.length());
}

void NetworkLogger::loop() {
    if (canBuffer.unreadCount() < SEND_BUFFER_SIZE) {
        return;
    }

    AsyncUDPMessage udpMessage(SEND_BUFFER_SIZE * (sizeof(char*) + sizeof(CAN_Message)));
    for (int i = 0; i < SEND_BUFFER_SIZE; i++) {
        CAN_Message message = canBuffer.pop();
        udpMessage.write(message.timestamp >> 3 * 8);
        udpMessage.write(message.timestamp >> 2 * 8);
        udpMessage.write(message.timestamp >> 1 * 8);
        udpMessage.write(message.timestamp >> 0 * 8);

        udpMessage.write(message.id >> 3 * 8);
        udpMessage.write(message.id >> 2 * 8);
        udpMessage.write(message.id >> 1 * 8);
        udpMessage.write(message.id >> 0 * 8);

        udpMessage.write(message.len);

        udpMessage.write(message.rxBuf, 8);

        udpMessage.write('\0');
    }

    udp.broadcast(udpMessage);
}
