#include <Arduino.h>
#include <pb_arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>

// Protobuf generated file
#include "common.pb.h"

bool prefix(pb_ostream_t *stream, int msgid)
{
  return pb_write(stream, (uint8_t *)&msgid, sizeof(msgid));
}

void setup()
{
  Serial.begin(115200);
}

pb_istream_t istream = as_pb_istream(Serial);
pb_ostream_t ostream = as_pb_ostream(Serial);

// pb_istream_t istream = pb_istream_from_buffer(buffer, buffer_pos);
void loop()
{
  /*   uint8_t buffer[128];
    size_t buffer_pos = 0; */

  // read into buffer until end of stream packet
  /* while (Serial.available() > 0)
  {
    // add to buffer
    buffer[buffer_pos++] = Serial.read();
    if (buffer_pos >= sizeof(buffer))
    {
      // buffer is full, exit loop
      break;
    }
  } */

  if (Serial.available() < 5)
    return;

  // Read the message ID header
  uint8_t msgid;
  if (!pb_read(&istream, (uint8_t *)&msgid, sizeof(msgid)))
  {
    Serial.println("Failed to read ID");
    return;
  }

  // Read the message
  switch (msgid)
  {
  case croissantbit_Ping_msgid:
  {
    croissantbit_Ping ping;
    if (!pb_decode(&istream, croissantbit_Ping_fields, &ping))
      return;
    // Clear the buffer
    // memset(buffer, 0, sizeof(buffer));

    if (!prefix(&ostream, croissantbit_Pong_msgid))
      return;
    croissantbit_Pong pong = croissantbit_Pong_init_zero;
    if (!pb_encode(&ostream, croissantbit_Pong_fields, &pong))
    {
      Serial.println("Failed to encode");
      return;
    }
    break;
  }
  default:
    return;
  }
}