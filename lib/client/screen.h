#pragma once
#include <TFT_eSPI.h>
#include <SPI.h>

#include "main.pb.h"

struct Screen
{
public:
    TFT_eSPI tft;
    Screen();
};