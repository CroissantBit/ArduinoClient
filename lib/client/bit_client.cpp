#include "bit_client.h"

BitClient::BitClient(SerialConnection *connection, Screen *screen)
{
    this->connection = connection;
    this->screen = screen;
}

BitClient::BitClient(SerialConnection *connection, Screen *screen, int btnPinUp, int btnPinDown, int btnPinLeft, int btnPinRight)
{
    this->connection = connection;
    this->screen = screen;

    this->btnPinUp = btnPinUp;
    this->btnPinDown = btnPinDown;
    this->btnPinLeft = btnPinLeft;
    this->btnPinRight = btnPinRight;

    // Enable internal pullup resistors
    pinMode(btnPinUp, INPUT_PULLUP);
    pinMode(btnPinDown, INPUT_PULLUP);
    pinMode(btnPinLeft, INPUT_PULLUP);
    pinMode(btnPinRight, INPUT_PULLUP);
}

bool BitClient::registerClient(croissantbit_RegisterClientRequest *registerClientRequest)
{
    return connection->send(&croissantbit_RegisterClientRequest_msg, croissantbit_RegisterClientRequest_msgid, &registerClientRequest);
}

void BitClient::checkSignalInputs()
{
    auto currentMillis = millis();
    if (currentMillis - signal_check_timestamp < SIGNAL_CHECK_INTERVAL)
        return;
    signal_check_timestamp = currentMillis;

    croissantbit_SignalUpdateRequest signalUpdateRequest = croissantbit_SignalUpdateRequest_init_zero;
    if (digitalRead(btnPinUp) == LOW)
    {
        signalUpdateRequest.direction = croissantbit_SignalDirection_UP;
        connection->send(&croissantbit_SignalUpdateRequest_msg, croissantbit_SignalUpdateRequest_msgid, &signalUpdateRequest);
    }
    else if (digitalRead(btnPinDown) == LOW)
    {
        signalUpdateRequest.direction = croissantbit_SignalDirection_DOWN;
        connection->send(&croissantbit_SignalUpdateRequest_msg, croissantbit_SignalUpdateRequest_msgid, &signalUpdateRequest);
    }
    else if (digitalRead(btnPinLeft) == LOW)
    {
        signalUpdateRequest.direction = croissantbit_SignalDirection_LEFT;
        connection->send(&croissantbit_SignalUpdateRequest_msg, croissantbit_SignalUpdateRequest_msgid, &signalUpdateRequest);
    }
    else if (digitalRead(btnPinRight) == LOW)
    {
        signalUpdateRequest.direction = croissantbit_SignalDirection_RIGHT;
        connection->send(&croissantbit_SignalUpdateRequest_msg, croissantbit_SignalUpdateRequest_msgid, &signalUpdateRequest);
    }
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
    if (currentMillis - keepalive_probe_timestamp >= keepalive_interval)
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

void BitClient::handleSignalStateUpdateMsg(croissantbit_SignalStateUpdate *signalStateUpdate)
{
    screen->displayArrow(signalStateUpdate->direction, TFT_WHITE);
}

void BitClient::handleVideoFrameUpdateMsg(croissantbit_VideoFrameUpdate *videoFrameUpdate)
{
    if (videoFrameUpdate->has_pixel != true)
        return;

    int x = videoFrameUpdate->pixel.x;
    int y = videoFrameUpdate->pixel.y;
    uint32_t color = getNearestColor(videoFrameUpdate->pixel.color);

    screen->tft.drawFastHLine(x, y, videoFrameUpdate->pixel.count, color);
}