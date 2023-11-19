#include "connection.h"

bool Connection::prefixMsg(int msgid)
{
    return pb_write(&ostream, (uint8_t *)&msgid, sizeof(msgid));
}

bool Connection::receive(void (*callback)(int, void *))
{
    int msgid;
    if (!pb_read(&istream, (uint8_t *)&msgid, sizeof(msgid)))
        return false;

    switch (msgid)
    {
    case croissantbit_Ping_msgid:
    {
        croissantbit_Ping message = croissantbit_Ping_init_zero;
        if (!pb_decode(&istream, &croissantbit_Ping_msg, &message))
            return false;
        callback(msgid, &message);
        break;
    }

    default:
        return false;
    }

    return true;
}