/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer
File Name : Grid.h
Description : grid function prototypes and shot result enum
Author : Campbell Roberts
Mail : Campbell.Roberts@mds.ac.nz
**************************************************************************/
#pragma once
#include "Constants.h"
#include "Fleet.h"
void FillGrid(char _cGrid[GRIDSIZE][GRIDSIZE]);
void DrawGrid(char _cGrid[GRIDSIZE][GRIDSIZE], int _iLeft, int _iTop, bool _bShowShips);
void DrawLabels(int _iLeft, int _iTop);
bool PlaceShip(char _cGrid[GRIDSIZE][GRIDSIZE], int _iRow, int _iCol, int _iLength, bool _bHorizontal, CFleet* _pFleet = nullptr);
void AutoPlaceShips(char _cGrid[GRIDSIZE][GRIDSIZE], CFleet* _pFleet = nullptr);
enum EShotResult
{
    SHOT_REPEAT = 0,
    SHOT_MISS = 1,
    SHOT_HIT = 2
};

EShotResult FireShot(char& _rcCell);
bool HasShips(char _cGrid[GRIDSIZE][GRIDSIZE]);
EShotResult ComputerShoot(char _cGrid[GRIDSIZE][GRIDSIZE], int& _riRow, int& _riCol);