#pragma once
#include "Constants.h"
void FillGrid(char _cGrid[GRIDSIZE][GRIDSIZE]);
void DrawGrid(char _cGrid[GRIDSIZE][GRIDSIZE], int _iLeft, int _iTop, bool _bShowShips);
void DrawLabels(int _iLeft, int _iTop);
bool PlaceShip(char _cGrid[GRIDSIZE][GRIDSIZE], int _iRow, int _iCol, int _iLength, bool _bHorizontal);
void AutoPlaceShips(char _cGrid[GRIDSIZE][GRIDSIZE]);