#include <Arduino.h>
#include "serial_connection.h"

SerialConnection::SerialConnection()
{
    istream = as_pb_istream(cobs_in);
    ostream = as_pb_ostream(cobs_out);
}

void SerialConnection::open(unsigned long baud_rate)
{
    Serial.begin(baud_rate);
}

void SerialConnection::close()
{
    Serial.end();
}

bool SerialConnection::send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct)
{
    if (!prefixMsg(msg_id))
        return false;
    return pb_encode(&ostream, field, msg_struct);
}
