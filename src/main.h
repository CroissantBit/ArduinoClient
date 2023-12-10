#include <Arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include "serial_connection.h"
#include "bit_client.h"

// Protobuf generated file
#include "main.pb.h"

#define ERROR_LED_OUT 13
#define WARN_LED_OUT 13

#define HANDLE_MSG_CASE(msg_id, type, code)                          \
    case msg_id:                                                     \
    {                                                                \
        [[maybe_unused]] auto msg = static_cast<type *>(msg_struct); \
        code;                                                        \
        break;                                                       \
    }

#define ERROR_OUT() digitalWrite(ERROR_LED_OUT, HIGH)
#define WARN_OUT() digitalWrite(WARN_LED_OUT, HIGH)

void handleMsg(int msg_id, void *msg_struct);