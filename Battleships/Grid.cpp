#include <iostream>
#include <cstdlib>
#include "Grid.h"
#include "Console.h"

using namespace std;
//fill grid with the ocean (#)
void FillGrid(char _cGrid[GRIDSIZE][GRIDSIZE])
{
    for (int iRow = 0; iRow < GRIDSIZE; ++iRow)
    {
        for (int iCol = 0; iCol < GRIDSIZE; ++iCol)
        {
            _cGrid[iRow][iCol] = OCEAN;
        }
    }
}

void DrawGrid(char _cGrid[GRIDSIZE][GRIDSIZE], int _iLeft, int _iTop, bool _bShowShips)
{
    for (int iRow = 0; iRow < GRIDSIZE; ++iRow)
    {
        for (int iCol = 0; iCol < GRIDSIZE; ++iCol)
        {
            //hide ships if not showing them
            char cShow = _cGrid[iRow][iCol];
            if (cShow == SHIP && !_bShowShips)
            {
                cShow = OCEAN;
            }
            // Choose a colour based on what is in this cell.
            switch (cShow)
            {
            case OCEAN:
            {
                SetRgb(COLOUR_BLUE_ON_BLACK);
                break;
            }
            case HIT:
            {
                SetRgb(COLOUR_RED_ON_BLACK);
                break;
            }
            case MISS:
            {
                SetRgb(COLOUR_YELLOW_ON_BLACK);
                break;
            }
            case SHIP:
            {
                SetRgb(COLOUR_GREEN_ON_BLACK);
                break;
            }
            default:
            {
                SetRgb(COLOUR_WHITE_ON_BLACK);
                break;
            }
            }

            // Move to this cell's position and print it two characters wide.
            GotoXY(_iLeft + 1 + (iCol * CELLWIDTH), _iTop + 1 + iRow);
            cout << cShow << " ";
        }
    }

    SetRgb(COLOUR_WHITE_ON_BLACK);
}
void DrawLabels(int _iLeft, int _iTop)
{
    SetRgb(COLOUR_GREEN_ON_BLACK);

    // letters across the top
    for (int iCol = 0; iCol < GRIDSIZE; ++iCol)
    {
        GotoXY(_iLeft + 1 + (iCol * CELLWIDTH), _iTop - 1);
        cout << char('A' + iCol);
    }

    // numbers down the side
    for (int iRow = 0; iRow < GRIDSIZE; ++iRow)
    {
        GotoXY(_iLeft - 3, _iTop + 1 + iRow);
        cout << iRow + 1;
    }

    SetRgb(COLOUR_WHITE_ON_BLACK);
}
bool PlaceShip(char _cGrid[GRIDSIZE][GRIDSIZE], int _iRow, int _iCol, int _iLength, bool _bHorizontal)
{
    // first pass only checks every cell the ship would use
    for (int iIndex = 0; iIndex < _iLength; ++iIndex)
    {
        int iCheckRow = _iRow;
        int iCheckCol = _iCol;

        if (_bHorizontal)
        {
            iCheckCol = _iCol + iIndex;
        }
        else
        {
            iCheckRow = _iRow + iIndex;
        }

        if (iCheckRow < 0 || iCheckRow >= GRIDSIZE || iCheckCol < 0 || iCheckCol >= GRIDSIZE)
        {
            return false;
        }

        // something already there
        if (_cGrid[iCheckRow][iCheckCol] != OCEAN)
        {
            return false;
        }
    }

    // second pass actually places it
    for (int iIndex = 0; iIndex < _iLength; ++iIndex)
    {
        if (_bHorizontal)
        {
            _cGrid[_iRow][_iCol + iIndex] = SHIP;
        }
        else
        {
            _cGrid[_iRow + iIndex][_iCol] = SHIP;
        }
    }

    return true;
}

void AutoPlaceShips(char _cGrid[GRIDSIZE][GRIDSIZE])
{
    int iShipLengths[NUMSHIPS] = { 5, 4, 3, 3, 2 };

    for (int iShip = 0; iShip < NUMSHIPS; ++iShip)
    {
        bool bPlaced = false;

        // keep trying random spots until the ship fits
        while (!bPlaced)
        {
            int iRow = rand() % GRIDSIZE;
            int iCol = rand() % GRIDSIZE;
            bool bHorizontal = (rand() % 2 == 0);

            bPlaced = PlaceShip(_cGrid, iRow, iCol, iShipLengths[iShip], bHorizontal);
        }
    }
}