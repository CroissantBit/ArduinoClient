#include "serial_connection.h"

SerialConnection::SerialConnection() {}

void SerialConnection::setHandlers(void (*packetCallback)(const uint8_t *buffer, size_t size), void (*msgCallback)(int, void *))
{
    packetSerial.setPacketHandler(packetCallback);
    SerialConnection::msgHandler = msgCallback;
}

void SerialConnection::open(unsigned long baud_rate)
{
    packetSerial.begin(baud_rate);
}

void SerialConnection::close()
{
    packetSerial.~PacketSerial_();
    Serial.end();
}

bool SerialConnection::send(const pb_msgdesc_t *field, const int msg_id, const void *msg_struct, const size_t msg_size)
{
    uint8_t buf[msg_size + sizeof(msg_id)] = {0};
    pb_ostream_t ostream = pb_ostream_from_buffer(buf, sizeof(buf));

    if (!pb_write(&ostream, (pb_byte_t *)&msg_id, sizeof(msg_id)))
        return false;
    if (!pb_encode(&ostream, field, msg_struct))
        return false;

    packetSerial.send(buf, sizeof(buf));
    return true;
}

void SerialConnection::receivePacket(const uint8_t *buffer, size_t size)
{
    // Not the greatest way to do this, should look into using a stream
    pb_istream_t istream = pb_istream_from_buffer(buffer, size);
    int msgid = 0;
    if (!pb_read(&istream, (pb_byte_t *)&msgid, sizeof(msgid)))
        return;

    switch (msgid)
    {
        HANDLE_RAW_MSG_CASE(croissantbit_Ping_msgid, croissantbit_Ping);
        HANDLE_RAW_MSG_CASE(croissantbit_Pong_msgid, croissantbit_Pong);
        HANDLE_RAW_MSG_CASE(croissantbit_RegisterClientResponse_msgid, croissantbit_RegisterClientResponse);
    }
}
