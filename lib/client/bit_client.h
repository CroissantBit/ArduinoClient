#pragma once
#include "serial_connection.h"
#include "screen.h"
#include "color.h"
#include "main.pb.h"

#define DEFAULT_KEEPALIVE_INTERVAL 8000
#define DEFAULT_KEEPALIVE_RETRIES 15
#define SIGNAL_CHECK_INTERVAL 100

struct BitClient
{
public:
    int clientId;
    croissantbit_PlayerState playerState;
    Screen *screen;

    BitClient(SerialConnection *connection, Screen *screen);
    BitClient(SerialConnection *connection, Screen *screen, int btnPinUp, int btnPinDown, int btnPinLeft, int btnPinRight);
    bool registerClient();
    bool updateKeepaliveState();
    void checkSignalInputs();

    void handlePingMsg();
    void handlePongMsg();
    void handleRegisterClientResponseMsg(croissantbit_RegisterClientResponse *registerClientResponse);
    void handlePlayerStateUpdateMsg(croissantbit_PlayerStateUpdate *playerStateUpdate);
    void handleSignalStateUpdateMsg(croissantbit_SignalStateUpdate *signalStateUpdate);
    void handleSignalUpdateResponseMsg(croissantbit_SignalUpdateResponse *signalUpdateResponse);
    void handleVideoFrameUpdateMsg(croissantbit_VideoFrameUpdate *videoFrameUpdate);

private:
    bool sendPing();

    SerialConnection *connection;
    unsigned int keepalive_interval = DEFAULT_KEEPALIVE_INTERVAL;
    unsigned int keepalive_retries_left = DEFAULT_KEEPALIVE_RETRIES;
    unsigned long keepalive_probe_timestamp = 0;
    unsigned long signal_check_timestamp = 0;

    int btnPinUp, btnPinDown, btnPinLeft, btnPinRight;
};