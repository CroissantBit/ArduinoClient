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
  bitClient = new BitClient(connection, screen);

  connection->setHandlers([](const uint8_t *buffer, size_t size)
                          { connection->receivePacket(buffer, size); },
                          &handleMsg);
  connection->open(115200L);

  /*
  croissantbit_VideoFrameUpdate videoFrameUpdate = croissantbit_VideoFrameUpdate_init_zero;
   videoFrameUpdate.has_pixel = true;
   videoFrameUpdate.pixel.x = 30;
   videoFrameUpdate.pixel.y = 80;
   videoFrameUpdate.pixel.color = croissantbit_Color_PINK;

   connection->send(&croissantbit_VideoFrameUpdate_msg, croissantbit_VideoFrameUpdate_msgid, &videoFrameUpdate);
  */
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
    HANDLE_MSG_CASE(croissantbit_VideoFrameUpdate_msgid, croissantbit_VideoFrameUpdate, bitClient->handleVideoFrameUpdateMsg(msg));
    HANDLE_MSG_CASE(croissantbit_PlayerStateUpdate_msgid, croissantbit_PlayerStateUpdate, bitClient->handlePlayerStateUpdateMsg(msg));
  default:
    break;
  }
}
