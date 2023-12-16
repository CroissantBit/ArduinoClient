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

bool SerialConnection::send(const pb_msgdesc_t *field, const uint16_t msg_id, const void *msg_struct)
{
    size_t size = 0;
    if (!pb_get_encoded_size(&size, field, msg_struct))
        return false;

    uint8_t buf[size + sizeof(uint16_t)] = {0};
    pb_ostream_t ostream = pb_ostream_from_buffer(buf, sizeof(buf));

    if (!pb_write(&ostream, (pb_byte_t *)&msg_id, sizeof(msg_id)))
        return false;
    if (!pb_encode(&ostream, field, msg_struct))
        return false;

    packetSerial.send(buf, ostream.bytes_written);
    return true;
}

void SerialConnection::receivePacket(const uint8_t *buffer, size_t size)
{
    // Not the greatest way to do this, should look into using a stream
    pb_istream_t istream = pb_istream_from_buffer(buffer, size);
    uint16_t msgid = 0;
    if (!pb_read(&istream, (pb_byte_t *)&msgid, sizeof(uint16_t)))
        return;

    switch (msgid)
    {
        HANDLE_RAW_MSG_CASE(croissantbit_Ping_msgid, croissantbit_Ping);
        HANDLE_RAW_MSG_CASE(croissantbit_Pong_msgid, croissantbit_Pong);
        HANDLE_RAW_MSG_CASE(croissantbit_RegisterClientResponse_msgid, croissantbit_RegisterClientResponse);
        HANDLE_RAW_MSG_CASE(croissantbit_VideoFrameUpdate_msgid, croissantbit_VideoFrameUpdate);
        HANDLE_RAW_MSG_CASE(croissantbit_SignalStateUpdate_msgid, croissantbit_SignalStateUpdate);
        HANDLE_RAW_MSG_CASE(croissantbit_SignalUpdateResponse_msgid, croissantbit_SignalUpdateResponse);
        HANDLE_RAW_MSG_CASE(croissantbit_PlayerStateUpdate_msgid, croissantbit_PlayerStateUpdate);
    }
}
