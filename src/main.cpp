#include "main.h"

SerialConnection connection;
BitClient bitClient(&connection);

void setup()
{
  pinMode(ERROR_LED_OUT, OUTPUT);
  pinMode(WARN_LED_OUT, OUTPUT);

  connection.setHandlers([](const uint8_t *buffer, size_t size)
                         { connection.receivePacket(buffer, size); },
                         handleMsg);
  connection.open(115200L);

  croissantbit_RegisterClientRequest request = croissantbit_RegisterClientRequest_init_zero;
  request.has_video_info = true;
  request.video_info.has_resolution = true;
  request.video_info.color_depth = 8;
  request.video_info.resolution.width = 240;
  request.video_info.resolution.height = 280;
  request.has_signal_info = true;
  request.signal_info.supports_signals = true;
  request.has_audio_info = false;
  request.can_control = false;

  bitClient.registerClient(&request);
}

void loop()
{
  // Handle new client repsone
  connection.packetSerial.update();
  if (connection.packetSerial.overflow())
    return ERROR_OUT();
  if (bitClient.updateKeepaliveState())
    return ERROR_OUT();
}

void handleMsg(int msg_id, void *msg_struct)
{
  switch (msg_id)
  {
    HANDLE_MSG_CASE(croissantbit_Ping_msgid, croissantbit_Ping, bitClient.handlePingMsg());
    HANDLE_MSG_CASE(croissantbit_Pong_msgid, croissantbit_Pong, bitClient.handlePongMsg());
    HANDLE_MSG_CASE(croissantbit_RegisterClientResponse_msgid, croissantbit_RegisterClientResponse, bitClient.handleRegisterClientResponseMsg(msg));
  default:
    break;
  }
}
