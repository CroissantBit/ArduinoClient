#include <Arduino.h>
#include <pb_arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "serial_connection.h"

// Protobuf generated file
#include "main.pb.h"

void setup()
{
  SerialConnection connection;
  connection.open(115200);
}

void loop()
{
}
