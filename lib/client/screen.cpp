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

void Screen::displayArrow(croissantbit_SignalDirection direction, int tft_color)
{
    switch (direction)
    {
    case croissantbit_SignalDirection_UP:
        tft.drawFastVLine(arrowPosX, arrowPosY, arrowSize, tft_color);
        displayArrowHead(direction, arrowPosX, arrowPosY, arrowSize / 2, tft_color);
        break;
    case croissantbit_SignalDirection_DOWN:
        tft.drawFastVLine(arrowPosX, arrowPosY, arrowSize, tft_color);
        displayArrowHead(direction, arrowPosX, arrowPosY + arrowSize, arrowSize / 2, tft_color);
        break;
    case croissantbit_SignalDirection_LEFT:
        tft.drawFastHLine(arrowPosX, arrowPosY, arrowSize, tft_color);
        displayArrowHead(direction, arrowPosX, arrowPosY, arrowSize / 2, tft_color);
        break;
    case croissantbit_SignalDirection_RIGHT:
        tft.drawFastHLine(arrowPosX, arrowPosY, arrowSize, tft_color);
        displayArrowHead(direction, arrowPosX + arrowSize, arrowPosY, arrowSize / 2, tft_color);
        break;
    }
}

void Screen::displayArrowHead(croissantbit_SignalDirection direction, int lineEndX, int lineEndY, int length, int tft_color)
{
    switch (direction)
    {
    case croissantbit_SignalDirection_UP:
        tft.drawLine(lineEndX, lineEndY, lineEndX - length, lineEndY + length, tft_color);
        tft.drawLine(lineEndX, lineEndY, lineEndX + length, lineEndY + length, tft_color);
        break;

    case croissantbit_SignalDirection_DOWN:
        tft.drawLine(lineEndX, lineEndY, lineEndX - length, lineEndY - length, tft_color);
        tft.drawLine(lineEndX, lineEndY, lineEndX + length, lineEndY - length, tft_color);
        break;

    case croissantbit_SignalDirection_LEFT:
        tft.drawLine(lineEndX, lineEndY, lineEndX + length, lineEndY + length, tft_color);
        tft.drawLine(lineEndX, lineEndY, lineEndX + length, lineEndY - length, tft_color);
        break;

    case croissantbit_SignalDirection_RIGHT:
        tft.drawLine(lineEndX, lineEndY, lineEndX - length, lineEndY + length, tft_color);
        tft.drawLine(lineEndX, lineEndY, lineEndX - length, lineEndY - length, tft_color);
        break;
    }
}
