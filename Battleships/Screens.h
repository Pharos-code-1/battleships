#pragma once
#include "Constants.h"
void PrintHeader();
void PrintAscii();
void DrawBox(int _iLeft, int _iTop, int _iWidth, int _iHeight);
void DrawFrameLine(int _iY, char _cFill);
void DrawFrameSides(int _iTop, int _iBottom);
void DrawPlayScreen(char _cPlayerGrid[GRIDSIZE][GRIDSIZE], char _cEnemyGrid[GRIDSIZE][GRIDSIZE]);