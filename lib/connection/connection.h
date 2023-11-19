#pragma once
#include <Arduino.h>
#include <cobs/Stream.h>
#include <cobs/Print.h>
#include <pb_arduino.h>
#include "main.pb.h"

struct Connection
{
protected:
    pb_istream_t istream;
    pb_ostream_t ostream;

    bool prefixMsg(int msgid);

public:
    virtual void open(unsigned long baud_rate){};
    virtual void close() = 0;
    virtual bool send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct) = 0;
    bool receive(void (*callback)(int, void *));
};
