#pragma once
#include "connection.h"
#include "main.pb.h"

#define DEFAULT_KEEPALIVE_INTERVAL 5000
#define DEFAULT_KEEPALIVE_RETRIES 3

struct BitClient
{
public:
    int clientId;

    BitClient(Connection *connection);
    bool registerClient(croissantbit_RegisterClientRequest registerClientRequest);
    bool trySendPing();
    void handleMsg(int msg_id, void *msg_struct);

private:
    bool sendPing();

    Connection *connection;
    unsigned int keepalive_interval = DEFAULT_KEEPALIVE_INTERVAL;
    unsigned int keepalive_retries = DEFAULT_KEEPALIVE_RETRIES;
    unsigned long last_keepalive_probe_timestamp = 0;
};