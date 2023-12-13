#include "main.h"

SerialConnection *connection;
BitClient *bitClient;
Screen *screen;

void setup()
{
  pinMode(ERROR_LED_OUT, OUTPUT);
  pinMode(WARN_LED_OUT, OUTPUT);

  connection = new SerialConnection();
  bitClient = new BitClient(connection);
  screen = new Screen();

  connection->setHandlers([](const uint8_t *buffer, size_t size)
                          { connection->receivePacket(buffer, size); },
                          &handleMsg);
  connection->open(115200L);
}

void loop()
{
  // Handle new client repsone
  connection->packetSerial.update();
  if (connection->packetSerial.overflow())
    return ERROR_OUT();
  if (bitClient->updateKeepaliveState())
    return ERROR_OUT();
}

void handleMsg(int msg_id, void *msg_struct)
{
  switch (msg_id)
  {
    HANDLE_MSG_CASE(croissantbit_Ping_msgid, croissantbit_Ping, bitClient->handlePingMsg());
    HANDLE_MSG_CASE(croissantbit_Pong_msgid, croissantbit_Pong, bitClient->handlePongMsg());
    HANDLE_MSG_CASE(croissantbit_RegisterClientResponse_msgid, croissantbit_RegisterClientResponse, bitClient->handleRegisterClientResponseMsg(msg));
  default:
    break;
  }
}
