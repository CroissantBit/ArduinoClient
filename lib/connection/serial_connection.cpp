#include <Arduino.h>
#include "serial_connection.h"

SerialConnection::SerialConnection()
{
    istream = as_pb_istream(Serial);
    ostream = as_pb_ostream(Serial);
}

void SerialConnection::open(int baud_rate)
{
    Serial.begin(baud_rate);
}

void SerialConnection::close()
{
    Serial.end();
}

bool SerialConnection::send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct)
{
    if (!prefixMsg(&ostream, msg_id))
        return false;
    return pb_encode(&ostream, field, msg_struct);
}
