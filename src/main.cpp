#include <Arduino.h>
#include <pb_arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>

// Protobuf generated file
#include "common.pb.c"

bool prefix(pb_ostream_t *stream, int msgid)
{
  return pb_write(stream, (uint8_t *)&msgid, sizeof(msgid));
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  SimpleMessage message = SimpleMessage_init_zero;

  pb_ostream_t stream = as_pb_ostream(Serial);

  /* Fill in the lucky number */
  message.lucky_number = 13;
  strcpy(message.message, "Hello world!");

  /* Now we are ready to encode the message! */
  prefix(&stream, 1);
  status = pb_encode(&stream, &SimpleMessage_msg, &message);
  message_length = stream.bytes_written;

  /* Then just check for any errors.. */
  if (!status)
  {
    Serial.print("Encoding failed: ");
    Serial.println(PB_GET_ERROR(&stream));
    return;
  }
  delay(2000);
}