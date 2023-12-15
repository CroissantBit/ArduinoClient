#pragma once
#include <TFT_eSPI.h>

#include <main.pb.h>

struct Screen
{
public:
    TFT_eSPI tft;
    Screen();

    void displayArrow(croissantbit_SignalDirection, int tft_color);

private:
    int arrowPosX = tft.width() - 40;
    int arrowPosY = tft.height() - 40;
    int arrowSize = 15;

    void displayArrowHead(croissantbit_SignalDirection direction, int lineMidX, int lineMidY, int length, int tft_color);
};