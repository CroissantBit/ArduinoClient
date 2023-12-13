#pragma once
#include <TFT_eSPI.h>
#include <SPI.h>

struct Screen
{
public:
    TFT_eSPI tft;
    Screen();
};