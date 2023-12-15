#include "main.h"

SerialConnection *connection;
Screen *screen;
BitClient *bitClient;

void setup()
{
  pinMode(ERROR_LED_PIN, OUTPUT);
  pinMode(WARN_LED_PIN, OUTPUT);

  connection = new SerialConnection();
  screen = new Screen();
  bitClient = new BitClient(connection, screen, BTN_UP_PIN, BTN_DOWN_PIN, BTN_LEFT_PIN, BTN_RIGHT_PIN);

  connection->setHandlers([](const uint8_t *buffer, size_t size)
                          { connection->receivePacket(buffer, size); },
                          &handleMsg);
  connection->open(115200L);
}

void loop()
{
  // Handle new client repsone
  bitClient->checkSignalInputs();
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
    HANDLE_MSG_CASE(croissantbit_VideoFrameUpdate_msgid, croissantbit_VideoFrameUpdate, bitClient->handleVideoFrameUpdateMsg(msg));
    HANDLE_MSG_CASE(croissantbit_SignalStateUpdate_msgid, croissantbit_SignalStateUpdate, bitClient->handleSignalStateUpdateMsg(msg));
    HANDLE_MSG_CASE(croissantbit_PlayerStateUpdate_msgid, croissantbit_PlayerStateUpdate, bitClient->handlePlayerStateUpdateMsg(msg));
  default:
    break;
  }
}
