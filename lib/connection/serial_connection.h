#pragma once
#include "connection.h"

struct SerialConnection : public Connection
{
protected:
    packetio::COBSStream cobs_in;
    packetio::COBSPrint cobs_out;

public:
    SerialConnection();
    void open(unsigned long baud_rate);
    bool send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct);
    void close();
};