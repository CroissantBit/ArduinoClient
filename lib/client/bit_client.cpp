#include "bit_client.h"

BitClient::BitClient(Connection *connection)
{
    this->connection = connection;
}

bool BitClient::registerClient(croissantbit_RegisterClientRequest registerClientRequest)
{
    return connection->send(&croissantbit_RegisterClientRequest_msg, croissantbit_RegisterClientRequest_msgid, &registerClientRequest);
}

/*
 * Returns true if the ping was sent, false if the ping either failed to be sent or wasn't sent because the keepalive interval hasn't passed yet.
 * Should be called in the main loop.
 */
bool BitClient::trySendPing()
{
    unsigned long currentMillis = millis();
    if (currentMillis - last_keepalive_probe_timestamp >= keepalive_interval)
    {
        last_keepalive_probe_timestamp = currentMillis;
        return sendPing();
    }
    return false;
}

bool BitClient::sendPing()
{
    if (keepalive_retries == 0)
    {
        connection->close();
        return false;
    }
    keepalive_retries--;
    return connection->send(&croissantbit_Ping_msg, croissantbit_Ping_msgid, croissantbit_Ping_init_zero);
}

void BitClient::handleMsg(int msg_id, void *msg_struct)
{
    switch (msg_id)
    {
    case croissantbit_Ping_msgid:
    {
        connection->send(&croissantbit_Pong_msg, croissantbit_Pong_msgid, croissantbit_Pong_init_zero);
        break;
    }
    case croissantbit_Pong_msgid:
    {
        keepalive_retries = DEFAULT_KEEPALIVE_RETRIES;
        break;
    }

    default:
        break;
    }
}
