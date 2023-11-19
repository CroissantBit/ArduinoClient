#pragma once
#include "pb_arduino.h"
#include "cobs/Stream.h"

struct Connection
{
protected:
    packetio::COBSStream cobs_in;
    packetio::COBSStream cobs_out;

    pb_istream_t *istream;
    pb_ostream_t *ostream;

    bool prefixMsg(int msgid);
    bool sendKeepAlive();

public:
    virtual void open(unsigned long baud_rate){};
    virtual void close() = 0;
    virtual bool send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct) = 0;
    bool receive(void (*callback)(int, void *));
};
