#pragma once
#include "Constants.h"

bool ReadShipInput(int& _riRow, int& _riCol, bool& _rbHorizontal);
void ManualPlaceShips(char _cGrid[GRIDSIZE][GRIDSIZE]);