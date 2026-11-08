#include <windows.h>
#pragma once
// Colour options for console text.
enum EColour
{
    COLOUR_WHITE_ON_BLACK = 0,
    COLOUR_RED_ON_BLACK = 1,
    COLOUR_GREEN_ON_BLACK = 2,
    COLOUR_YELLOW_ON_BLACK = 3,
    COLOUR_BLUE_ON_BLACK = 4,
    COLOUR_MAGENTA_ON_BLACK = 5,
    COLOUR_CYAN_ON_BLACK = 6,
    COLOUR_BLACK_ON_GRAY = 7,
    COLOUR_BLACK_ON_WHITE = 8,
    COLOUR_RED_ON_WHITE = 9,
    COLOUR_GREEN_ON_WHITE = 10,
    COLOUR_YELLOW_ON_WHITE = 11,
    COLOUR_BLUE_ON_WHITE = 12,
    COLOUR_MAGENTA_ON_WHITE = 13,
    COLOUR_CYAN_ON_WHITE = 14,
    COLOUR_WHITE_ON_WHITE = 15
};

// Functions.
void ClearScreen();
void GotoXY(int _iX, int _iY);
void SetRgb(EColour _eColour);