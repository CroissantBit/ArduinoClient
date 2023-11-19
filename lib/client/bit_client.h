#pragma once
#include "connection.h"
#include "main.pb.h"

struct BitClient
{
public:
    int clientId;

    BitClient(Connection *connection);
    bool registerClient(croissantbit_RegisterClientRequest registerClientRequest);
    bool handleMsg();

private:
    Connection *connection;
};