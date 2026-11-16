/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer
File Name : Input.h
Description : input function prototypes
Author : Campbell Roberts
Mail : Campbell.Roberts@mds.ac.nz
**************************************************************************/
#pragma once
#include "Constants.h"
#include "Fleet.h"
bool ReadShipInput(int& _riRow, int& _riCol, bool& _rbHorizontal);
void ManualPlaceShips(char _cGrid[GRIDSIZE][GRIDSIZE], CFleet* _pFleet);
bool ReadTarget(int& _riRow, int& _riCol);