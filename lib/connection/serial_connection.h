#pragma once
#include "connection.h"

struct SerialConnection : public Connection
{
public:
    SerialConnection();
    void open(unsigned long baud_rate);
    void close();
    bool send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct);
};