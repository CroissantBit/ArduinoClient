#include "screen.h"

Screen::Screen()
{
    tft = TFT_eSPI();

    tft.init();
    tft.setRotation(2);
    tft.fillScreen(0x5AEB);
}
