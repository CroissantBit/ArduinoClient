#include "bit_client.h"

BitClient::BitClient(SerialConnection *connection, Screen *screen)
{
    this->connection = connection;
    this->screen = screen;
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

void BitClient::handlePlayerStateUpdateMsg(croissantbit_PlayerStateUpdate *playerStateUpdate)
{
    playerState = playerStateUpdate->state;
}

// Returns the color that is closest to tft.h
uint32_t GetNearestColor(croissantbit_Color color)
{
    switch (color)
    {
    case croissantbit_Color_BLACK:
        return TFT_BLACK;
    case croissantbit_Color_NAVY:
        return TFT_NAVY;
    case croissantbit_Color_DARKGREEN:
        return TFT_DARKGREEN;
    case croissantbit_Color_DARKCYAN:
        return TFT_DARKCYAN;
    case croissantbit_Color_MAROON:
        return TFT_MAROON;
    case croissantbit_Color_PURPLE:
        return TFT_PURPLE;
    case croissantbit_Color_OLIVE:
        return TFT_OLIVE;
    case croissantbit_Color_LIGHTGREY:
        return TFT_LIGHTGREY;
    case croissantbit_Color_DARKGREY:
        return TFT_DARKGREY;
    case croissantbit_Color_BLUE:
        return TFT_BLUE;
    case croissantbit_Color_GREEN:
        return TFT_GREEN;
    case croissantbit_Color_CYAN:
        return TFT_CYAN;
    case croissantbit_Color_RED:
        return TFT_RED;
    case croissantbit_Color_MAGENTA:
        return TFT_MAGENTA;
    case croissantbit_Color_YELLOW:
        return TFT_YELLOW;
    case croissantbit_Color_WHITE:
        return TFT_WHITE;
    case croissantbit_Color_ORANGE:
        return TFT_ORANGE;
    case croissantbit_Color_GREENYELLOW:
        return TFT_GREENYELLOW;
    case croissantbit_Color_PINK:
        return TFT_PINK;
    default:
        return TFT_BLACK;
    }
}

void BitClient::handleVideoFrameUpdateMsg(croissantbit_VideoFrameUpdate *videoFrameUpdate)
{
    if (videoFrameUpdate->has_pixel != true)
        return;

    int x = videoFrameUpdate->pixel.x;
    int y = videoFrameUpdate->pixel.y;
    uint32_t color = GetNearestColor(videoFrameUpdate->pixel.color);

    screen->tft.drawFastHLine(x, y, videoFrameUpdate->pixel.count, color);
}