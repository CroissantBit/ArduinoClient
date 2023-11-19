#include "bit_client.h"
#include "main.pb.h"

BitClient::BitClient(Connection *connection)
{
    this->connection = connection;
}

bool BitClient::registerClient(croissantbit_RegisterClientRequest registerClientRequest)
{
    return connection->send(&croissantbit_Ping_msg, croissantbit_Ping_msgid, croissantbit_Ping_init_zero);
}

bool BitClient::handleMsg()
{
    return true;
}
