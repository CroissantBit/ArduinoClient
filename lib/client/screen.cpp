#include "screen.h"

Screen::Screen()
{
    tft = TFT_eSPI();

    tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);

    displayStatus(TFT_WHITE);
}

void Screen::displayStatus(int tft_color)
{
    auto middleX = tft.width() / 2;
    auto middleY = tft.height() / 2;
    auto gap = 20;
    tft.fillCircle(middleX - gap, middleY, 3, tft_color);
    tft.fillCircle(middleX, middleY, 3, tft_color);
    tft.fillCircle(middleX + gap, middleY, 3, tft_color);
}

void Screen::displaySignal(int tft_color)
{
    tft.fillCircle(itemsPosX, itemsPosY - arrowSize * 2, 6, tft_color);
}

void Screen::displayArrow(croissantbit_SignalDirection direction, int tft_color)
{
    tft.fillRect(itemsPosX - arrowSize, itemsPosY - arrowSize, itemsPosX + arrowSize, itemsPosY + arrowSize, TFT_BLACK);
    switch (direction)
    {
    case croissantbit_SignalDirection_UP:
        tft.drawFastVLine(itemsPosX, itemsPosY, arrowSize, tft_color);
        displayArrowHead(direction, itemsPosX, itemsPosY, arrowSize / 2, tft_color);
        break;
    case croissantbit_SignalDirection_DOWN:
        tft.drawFastVLine(itemsPosX, itemsPosY, arrowSize, tft_color);
        displayArrowHead(direction, itemsPosX, itemsPosY + arrowSize, arrowSize / 2, tft_color);
        break;
    case croissantbit_SignalDirection_LEFT:
        tft.drawFastHLine(itemsPosX, itemsPosY, arrowSize, tft_color);
        displayArrowHead(direction, itemsPosX, itemsPosY, arrowSize / 2, tft_color);
        break;
    case croissantbit_SignalDirection_RIGHT:
        tft.drawFastHLine(itemsPosX, itemsPosY, arrowSize, tft_color);
        displayArrowHead(direction, itemsPosX + arrowSize, itemsPosY, arrowSize / 2, tft_color);
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
