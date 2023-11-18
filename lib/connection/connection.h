#pragma once
#include "pb_arduino.h"

struct Connection
{
protected:
    bool prefixMsg(pb_ostream_t *stream, int msgid);

public:
    pb_istream_t istream;
    pb_ostream_t ostream;
    virtual bool open();
    virtual bool close();
    bool send();
};
