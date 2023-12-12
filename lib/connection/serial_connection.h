#pragma once
#include <PacketSerial.h>
#include <pb_decode.h>
#include <pb_encode.h>

#include "main.pb.h"

#define HANDLE_RAW_MSG_CASE(msg_id, type)               \
    case msg_id:                                        \
    {                                                   \
        type message = type##_init_zero;                \
        if (pb_decode(&istream, &type##_msg, &message)) \
            msgHandler(msg_id, &message);               \
        break;                                          \
    }

struct SerialConnection
{
private:
    // The callback for when a packet is decoded
    void (*msgHandler)(int, void *);

public:
    PacketSerial packetSerial;
    SerialConnection();
    void setHandlers(void (*packetCallback)(const uint8_t *buffer, size_t size), void (*msgCallback)(int, void *));

    void open(unsigned long baud_rate);
    void close();

    void update();
    bool send(const pb_msgdesc_t *field, const uint16_t msg_id, const void *msg_struct);
    void receivePacket(const uint8_t *buffer, size_t size);
};
