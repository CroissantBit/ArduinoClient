#include <Arduino.h>

#include "connection.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_arduino.h"

struct SerialConnection : public Connection
{
public:
    bool open()
    {
        // TODO: Read from config
        Serial.begin(115200);

        istream = as_pb_istream(Serial);
        ostream = as_pb_ostream(Serial);
    };

    bool close()
    {
        Serial.end();
    };
};
