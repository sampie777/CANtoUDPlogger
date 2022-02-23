//
// Created by samuel on 23-02-22.
//

#ifndef CANTOUDPLOGGER_CONFIG_H
#define CANTOUDPLOGGER_CONFIG_H

#define WIFI_SSID "ESP32 CAN"
#define WIFI_PASSWORD ""
#define UDP_PORT 2302

// Attach INT of MCP2515 to pin 2
#define CAN0_INT 27
// Attach CS of MCP2515 to pin 10
#define CAN0_CS 15

#define BUFFER_SIZE 64
#define SEND_BUFFER_SIZE 16

#endif //CANTOUDPLOGGER_CONFIG_H
