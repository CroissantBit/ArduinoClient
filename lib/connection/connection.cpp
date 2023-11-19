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
