#include "connection.h"

bool Connection::prefixMsg(pb_ostream_t *stream, int msgid)
{
    return pb_write(stream, (uint8_t *)&msgid, sizeof(msgid));
}
