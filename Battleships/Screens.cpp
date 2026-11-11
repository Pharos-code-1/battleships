#include <iostream>
#include "Screens.h"
#include "Console.h"
#include "Grid.h"


using namespace std;
void PrintHeader() {
    SetRgb(COLOUR_WHITE_ON_BLACK);
    cout << R"(
         |=================================================================================|
         |                _           _   _   _           _     _                          |
         |               | |         | | | | | |         | |   (_)                         |
         |               | |__   __ _| |_| |_| | ___  ___| |__  _ _ __  ___                |
         |               | '_ \ / _` | __| __| |/ _ \/ __| '_ \| | '_ \/ __|               |
         |               | |_) | (_| | |_| |_| |  __/\__ \ | | | | |_) \__ \               |
         |               |_.__/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/|___/               |
         |                                                     | |                         |
         |                                                     |_|                         | )" << endl;
} //https://ascii.co.uk/art/battleships
void PrintAscii() {

    SetRgb(COLOUR_BLUE_ON_BLACK);
    cout <<
        R"(         |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~oo~~~~~~~~~~~~~|#)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
         |                                 o o             |#                              |
         |                                o ooo            |#                              |
         |                                  o oo           |#                              |
         |                                     o o      |  |#                              |
         |                                      oo     _|__|#_                             |
         |                                        o   |   /   |                            |
         |   __                    ___________________|   \___|_________________           |
         |  |   -_______-----------                                              \         |
         | >|    _____                    >>>>         >>>>           >>>>        )        |
         |  |__ -     ---------_________________________________________________ /         |
         |                                                                                 |
         |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|)" << endl;
} //https://www.asciiart.eu/art/49d8fc2dbf033525

void DrawBox(int _iLeft, int _iTop, int _iWidth, int _iHeight)
{
    // Draw the top and bottom edges.
    for (int iX = 0; iX < _iWidth; ++iX)
    {
        GotoXY(_iLeft + iX, _iTop);
        cout << "-";
        GotoXY(_iLeft + iX, _iTop + _iHeight - 1);
        cout << "-";
    }

    // Draw the left and right edges.
    for (int iY = 1; iY < _iHeight - 1; ++iY)
    {
        GotoXY(_iLeft, _iTop + iY);
        cout << "|";
        GotoXY(_iLeft + _iWidth - 1, _iTop + iY);
        cout << "|";
    }
}

void DrawFrameLine(int _iY, char _cFill)
{
    GotoXY(FRAMELEFTX, _iY);
    cout << "|";
    for (int iX = FRAMELEFTX + 1; iX < FRAMERIGHTX; ++iX)
    {
        cout << _cFill;
    }
    cout << "|";
}

void DrawFrameSides(int _iTop, int _iBottom)
{
    for (int iY = _iTop; iY <= _iBottom; ++iY)
    {
        GotoXY(FRAMELEFTX, iY);
        cout << "|";
        GotoXY(FRAMERIGHTX, iY);
        cout << "|";
    }
}

void DrawPlayScreen(char _cPlayerGrid[GRIDSIZE][GRIDSIZE], char _cEnemyGrid[GRIDSIZE][GRIDSIZE])
{
    ClearScreen();
    PrintHeader();

    // blue wave under the title then white sides
    SetRgb(COLOUR_BLUE_ON_BLACK);
    DrawFrameLine(10, '~');
    SetRgb(COLOUR_WHITE_ON_BLACK);
    DrawFrameSides(11, 32);

    // player grid (left)
    SetRgb(COLOUR_YELLOW_ON_BLACK);
    DrawBox(PLAYERGRIDX, GRIDY, 22, 12);
    DrawGrid(_cPlayerGrid, PLAYERGRIDX, GRIDY, true);
    DrawLabels(PLAYERGRIDX, GRIDY);

    // enemy grid (right)
    SetRgb(COLOUR_YELLOW_ON_BLACK);
    DrawBox(ENEMYGRIDX, GRIDY, 22, 12);
    DrawGrid(_cEnemyGrid, ENEMYGRIDX, GRIDY, false);
    DrawLabels(ENEMYGRIDX, GRIDY);

    // red middle bar
    SetRgb(COLOUR_RED_ON_BLACK);
    for (int iY = 12; iY <= 32; ++iY)
    {
        GotoXY(DIVIDERX, iY);
        cout << "|";
    }

    // you and enemy text centred under each grid
    GotoXY(PLAYERGRIDX + 7, 25);
    cout << "--You--";
    GotoXY(ENEMYGRIDX + 6, 25);
    cout << "--Enemy--";

    // stats lines
    SetRgb(COLOUR_WHITE_ON_BLACK);
    GotoXY(PLAYERGRIDX + 7, 26);
    cout << "Shots:";
    GotoXY(PLAYERGRIDX + 7, 27);
    cout << "Hits:";
    GotoXY(PLAYERGRIDX + 7, 28);
    cout << "Misses:";
    GotoXY(ENEMYGRIDX + 6, 26);
    cout << "Shots:";
    GotoXY(ENEMYGRIDX + 6, 27);
    cout << "Hits:";
    GotoXY(ENEMYGRIDX + 6, 28);
    cout << "Misses:";

    // blue wave under the stats, crosses the bar
    SetRgb(COLOUR_BLUE_ON_BLACK);
    DrawFrameLine(29, '~');

    // placement boxes
    SetRgb(COLOUR_WHITE_ON_BLACK);
    GotoXY(PLACEMANUALX, 30);
    cout << "|  _  |";
    GotoXY(PLACEMANUALX, 31);
    cout << "| | | | Manual Ship Placement:";
    GotoXY(PLACEMANUALX, 32);
    cout << "|_____|";
    GotoXY(PLACEAUTOX, 30);
    cout << "|  _  |";
    GotoXY(PLACEAUTOX, 31);
    cout << "| | | | Auto Ship Placement:";
    GotoXY(PLACEAUTOX, 32);
    cout << "|_____|";

    // red numbers in the boxes
    SetRgb(COLOUR_RED_ON_BLACK);
    GotoXY(PLACEMANUALX + 3, 31);
    cout << "1";
    GotoXY(PLACEAUTOX + 3, 31);
    cout << "2";

    // yellow prompt frame same as the menu
    SetRgb(COLOUR_YELLOW_ON_BLACK);
    DrawFrameLine(33, '~');
    DrawFrameSides(34, 35);
    GotoXY(38, 35);
    cout << "Please enter your choice: ";
    DrawFrameLine(36, '=');

    // cursor after the prompt ready for input
    GotoXY(64, 35);
}
void ShowPrompt(const string& _sLine, const string& _sPrompt)
{
    // wipe the two rows inside the yellow frame
    for (int iY = PROMPTLINEY; iY <= PROMPTY; ++iY)
    {
        GotoXY(FRAMELEFTX + 1, iY);
        for (int iX = FRAMELEFTX + 1; iX < FRAMERIGHTX; ++iX)
        {
            cout << " ";
        }
    }

    // message on the top row and the prompt on the row below
    SetRgb(COLOUR_WHITE_ON_BLACK);
    GotoXY(PROMPTX, PROMPTLINEY);
    cout << _sLine;
    SetRgb(COLOUR_YELLOW_ON_BLACK);
    GotoXY(PROMPTX, PROMPTY);
    cout << _sPrompt;
}
void DrawStats(int _iX, int _iShots, int _iHits, int _iMisses)
{
    SetRgb(COLOUR_WHITE_ON_BLACK);
    GotoXY(_iX + 8, STATSY);
    cout << _iShots << "   ";
    GotoXY(_iX + 8, STATSY + 1);
    cout << _iHits << "   ";
    GotoXY(_iX + 8, STATSY + 2);
    cout << _iMisses << "   ";
}

void ClearPlacementBoxes()
{
    // wipe the 2 placement boxes
    for (int iY = PLACEBOXTOP; iY <= PLACEBOXBOTTOM; ++iY)
    {
        GotoXY(FRAMELEFTX + 1, iY);
        for (int iX = FRAMELEFTX + 1; iX < FRAMERIGHTX; ++iX)
        {
            cout << " ";
        }
    }

    // put the red bar back
    SetRgb(COLOUR_RED_ON_BLACK);
    for (int iY = PLACEBOXTOP; iY <= PLACEBOXBOTTOM; ++iY)
    {
        GotoXY(DIVIDERX, iY);
        cout << "|";
    }
}