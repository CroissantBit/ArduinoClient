#include "screen.h"

Screen::Screen()
{
    tft = TFT_eSPI();

    tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);

    // Draw 3 "waiting dots"
    auto middleX = tft.width() / 2;
    auto middleY = tft.height() / 2;
    auto gap = 20;
    tft.fillCircle(middleX - gap, middleY, 3, TFT_WHITE);
    tft.fillCircle(middleX, middleY, 3, TFT_WHITE);
    tft.fillCircle(middleX + gap, middleY, 3, TFT_WHITE);
}