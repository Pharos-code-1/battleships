#include <iostream>
#include <string>
#include "Input.h"
#include "Console.h"
#include "Grid.h"
#include "Screens.h"

using namespace std;

bool ReadShipInput(int& _riRow, int& _riCol, bool& _rbHorizontal) 
{
    char cLetter = ' ';
    int iNumber = 0;
    char cDirection = ' ';

    cin >> cLetter >> iNumber >> cDirection;

    // clear any bad input and throw away the rest of the line
    bool bFailed = cin.fail();
    cin.clear();
    cin.ignore(1000, '\n');

    if (bFailed)
    {
        return false;
    }

    // letter has to be a to j
    int iCol = 0;
    if (cLetter >= 'A' && cLetter <= 'J')
    {
        iCol = cLetter - 'A';
    }
    else if (cLetter >= 'a' && cLetter <= 'j')
    {
        iCol = cLetter - 'a';
    }
    else
    {
        return false;
    }

    // number has to be 1 to 10
    if (iNumber < 1 || iNumber > GRIDSIZE)
    {
        return false;
    }

    // direction has to be h or v
    if (cDirection == 'H' || cDirection == 'h')
    {
        _rbHorizontal = true;
    }
    else if (cDirection == 'V' || cDirection == 'v')
    {
        _rbHorizontal = false;
    }
    else
    {
        return false;
    }

    // all good so hand the values back
    _riRow = iNumber - 1;
    _riCol = iCol;
    return true;
}

void ManualPlaceShips(char _cGrid[GRIDSIZE][GRIDSIZE])
{
    for (int iShip = 0; iShip < NUMSHIPS; ++iShip)
    {
        bool bPlaced = false;
        string sLine = "Place your " + SHIPNAMES[iShip] + " (" + to_string(SHIPLENGTHS[iShip]) + " cells)";

        // keep asking until the ship is placed
        while (!bPlaced)
        {
            ShowPrompt(sLine, "Position and direction, eg B7 H: ");

            int iRow = 0;
            int iCol = 0;
            bool bHorizontal = true;

            if (ReadShipInput(iRow, iCol, bHorizontal))
            {
                bPlaced = PlaceShip(_cGrid, iRow, iCol, SHIPLENGTHS[iShip], bHorizontal);

                if (!bPlaced)
                {
                    ShowPrompt("That ship doesnt fit there, try again");
                    Sleep(1500);
                }
            }
            else
            {
                ShowPrompt("Invalid input, use a letter A-J, a number 1-10 and H or V");
                Sleep(1500);
            }
        }

        // redraw the grid so the ship shows
        DrawGrid(_cGrid, PLAYERGRIDX, GRIDY, true);
    }

    ShowPrompt("All ships placed");
}
bool ReadTarget(int& _riRow, int& _riCol)
{
    char cLetter = ' ';
    int iNumber = 0;

    cin >> cLetter >> iNumber;

    // clear any bad input and throw away the rest of the line
    bool bFailed = cin.fail();
    cin.clear();
    cin.ignore(1000, '\n');

    if (bFailed)
    {
        return false;
    }

    // letter has to be a to j
    int iCol = 0;
    if (cLetter >= 'A' && cLetter <= 'J')
    {
        iCol = cLetter - 'A';
    }
    else if (cLetter >= 'a' && cLetter <= 'j')
    {
        iCol = cLetter - 'a';
    }
    else
    {
        return false;
    }

    // number has to be 1 to 10
    if (iNumber < 1 || iNumber > GRIDSIZE)
    {
        return false;
    }

    // correct so sends values back
    _riRow = iNumber - 1;
    _riCol = iCol;
    return true;
}