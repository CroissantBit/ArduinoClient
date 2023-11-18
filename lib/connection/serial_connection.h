#pragma once
#include "connection.h"

struct SerialConnection : public Connection
{
public:
    SerialConnection();
    void open(int baud_rate);
    void close();
    bool send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct);
};