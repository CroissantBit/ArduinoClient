#pragma once
#include "main.pb.h"
#include "serial_connection.h"

#define DEFAULT_KEEPALIVE_INTERVAL 5000
#define DEFAULT_KEEPALIVE_RETRIES 10

struct BitClient
{
public:
    int clientId;
    croissantbit_PlayerState playerState;

    BitClient(SerialConnection *connection);
    bool registerClient(croissantbit_RegisterClientRequest *registerClientRequest);
    bool updateKeepaliveState();

    void handlePingMsg();
    void handlePongMsg();
    void handleRegisterClientResponseMsg(croissantbit_RegisterClientResponse *registerClientResponse);
    void handlePlayerStateUpdateMsg(croissantbit_PlayerStateUpdate *playerStateUpdate);

private:
    bool sendPing();

    SerialConnection *connection;
    unsigned int keepalive_interval = DEFAULT_KEEPALIVE_INTERVAL;
    unsigned int keepalive_retries_left = DEFAULT_KEEPALIVE_RETRIES;
    unsigned long keepalive_probe_timestamp = 0;
};