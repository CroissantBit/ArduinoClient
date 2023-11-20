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
    /*
     * Send a message to the current connection.
     * Returns true if the message was successfully sent.
     * @param field The message descriptor for the message to be sent.
     * @param msg_id The message ID for the message to be sent.
     * @param msg_struct The message struct for the message to be sent.
     */
    virtual bool send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct) = 0;
    /*
     * Receive a message from the connection.
     * The consumer of this function must provide a callback function that will be called when a message is received and successfully decoded.
     */
    bool receive(void (*callback)(int, void *));
};
