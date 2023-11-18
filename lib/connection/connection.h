#pragma once
#include "pb_arduino.h"

struct Connection
{
protected:
    pb_istream_t istream;
    pb_ostream_t ostream;
    bool prefixMsg(pb_ostream_t *stream, int msgid);

public:
    virtual void open(int baud_rate) = 0;
    virtual void close() = 0;
    virtual bool send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct) = 0;
};
