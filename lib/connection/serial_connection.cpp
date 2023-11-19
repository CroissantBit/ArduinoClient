#include "serial_connection.h"

SerialConnection::SerialConnection() : cobs_in(Serial), cobs_out(Serial)
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
    {
        cobs_out.abort();
        return false;
    }
    if (!pb_encode(&ostream, field, msg_struct))
    {
        cobs_out.abort();
        return false;
    }

    cobs_out.end();
    return true;
}