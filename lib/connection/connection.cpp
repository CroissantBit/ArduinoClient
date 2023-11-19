#include "connection.h"
#include "main.pb.h"

bool Connection::prefixMsg(int msgid)
{
    return pb_write(&ostream, (uint8_t *)&msgid, sizeof(msgid));
}

bool Connection::sendKeepAlive()
{
    return Connection::send(&croissantbit_Ping_msg, croissantbit_Ping_msgid, croissantbit_Ping_init_zero);
}

bool Connection::receive(void (*callback)(int, void *))
{
    int msgid;

    // Read the message ID
    if (!pb_read(&istream, (uint8_t *)&msgid, sizeof(msgid)))
    {
        // Handle error
        return false;
    }

    // Decode the message based on the message ID
    switch (msgid)
    {
    case croissantbit_Ping_msgid:
    {
        croissantbit_Ping message = croissantbit_Ping_init_zero;
        if (!pb_decode(&istream, croissantbit_Ping_fields, &message))
            return false;
        callback(msgid, &message);
        break;
    }

    default:
        return false;
    }

    return true;
}