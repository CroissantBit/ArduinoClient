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
}

void loop()
{
  client.trySendPing();
}
