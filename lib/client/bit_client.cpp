#include "bit_client.h"

BitClient::BitClient(SerialConnection *connection)
{
    this->connection = connection;
}

bool BitClient::registerClient(croissantbit_RegisterClientRequest *registerClientRequest)
{
    return connection->send(&croissantbit_RegisterClientRequest_msg, croissantbit_RegisterClientRequest_msgid, &registerClientRequest);
}

/*
 * Check if the connection is still alive and tries to send a ping if it is.
 * Should be called in the main loop.
 * @return false if the connection is still alive, true if it has been closed
 */
bool BitClient::updateKeepaliveState()
{
    if (keepalive_retries_left == 0)
    {
        connection->close();
        return true;
    }

    unsigned long currentMillis = millis();
    if (millis() - keepalive_probe_timestamp >= keepalive_interval)
    {
        keepalive_probe_timestamp = currentMillis;
        sendPing();
        return false;
    }
    return true;
}

bool BitClient::sendPing()
{

    keepalive_retries_left--;
    return connection->send(&croissantbit_Ping_msg, croissantbit_Ping_msgid, croissantbit_Ping_init_zero);
}

void BitClient::handlePingMsg()
{
    connection->send(&croissantbit_Pong_msg, croissantbit_Pong_msgid, croissantbit_Pong_init_zero);
}

void BitClient::handlePongMsg()
{
    keepalive_retries_left = DEFAULT_KEEPALIVE_RETRIES;
}

void BitClient::handleRegisterClientResponseMsg(croissantbit_RegisterClientResponse *registerClientResponse)
{
    clientId = registerClientResponse->client_id;
    playerState = registerClientResponse->state;
}
