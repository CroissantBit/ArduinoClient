#include "color.h"

uint32_t getNearestColor(croissantbit_Color color)
{
    switch (color)
    {
    case croissantbit_Color_BLACK:
        return TFT_BLACK;
    case croissantbit_Color_NAVY:
        return TFT_NAVY;
    case croissantbit_Color_DARKGREEN:
        return TFT_DARKGREEN;
    case croissantbit_Color_DARKCYAN:
        return TFT_DARKCYAN;
    case croissantbit_Color_MAROON:
        return TFT_MAROON;
    case croissantbit_Color_PURPLE:
        return TFT_PURPLE;
    case croissantbit_Color_OLIVE:
        return TFT_OLIVE;
    case croissantbit_Color_LIGHTGREY:
        return TFT_LIGHTGREY;
    case croissantbit_Color_DARKGREY:
        return TFT_DARKGREY;
    case croissantbit_Color_BLUE:
        return TFT_BLUE;
    case croissantbit_Color_GREEN:
        return TFT_GREEN;
    case croissantbit_Color_CYAN:
        return TFT_CYAN;
    case croissantbit_Color_RED:
        return TFT_RED;
    case croissantbit_Color_MAGENTA:
        return TFT_MAGENTA;
    case croissantbit_Color_YELLOW:
        return TFT_YELLOW;
    case croissantbit_Color_WHITE:
        return TFT_WHITE;
    case croissantbit_Color_ORANGE:
        return TFT_ORANGE;
    case croissantbit_Color_GREENYELLOW:
        return TFT_GREENYELLOW;
    case croissantbit_Color_PINK:
        return TFT_PINK;
    default:
        return TFT_BLACK;
    }
}