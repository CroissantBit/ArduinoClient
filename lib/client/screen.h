#pragma once
#include <TFT_eSPI.h>

#include <main.pb.h>

struct Screen
{
public:
    TFT_eSPI tft;
    Screen();

    void displayStatus(int tft_color);
    void displaySignal(int tft_color);
    void displayArrow(croissantbit_SignalDirection direction, int tft_color);

private:
    int itemsPosX = tft.width() / 2;
    int itemsPosY = tft.height() / 3;
    int arrowSize = 40;

    void displayArrowHead(croissantbit_SignalDirection direction, int lineMidX, int lineMidY, int length, int tft_color);
};