#include <Arduino.h>
#include <pb_arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include "serial_connection.h"
#include "bit_client.h"

// Protobuf generated file
#include "main.pb.h"

SerialConnection connection;
BitClient client(&connection);

void setup()
{
  connection.open(115200L);
  croissantbit_RegisterClientRequest registerClientRequest = croissantbit_RegisterClientRequest_init_zero;
  client.registerClient(registerClientRequest);
}

void loop()
{
  croissantbit_Ping ping = croissantbit_Ping_init_zero;
  connection.send(&croissantbit_Ping_msg, croissantbit_Ping_msgid, &ping);

  delay(3000);
}
