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

void DrawPlayScreen(char _cPlayerGrid[GRIDSIZE][GRIDSIZE], char _cEnemyGrid[GRIDSIZE][GRIDSIZE], bool _bDebug)
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
    DrawGrid(_cPlayerGrid, PLAYERGRIDX, GRIDY, !_bDebug);
    DrawLabels(PLAYERGRIDX, GRIDY);

    // enemy grid (right)
    SetRgb(COLOUR_YELLOW_ON_BLACK);
    DrawBox(ENEMYGRIDX, GRIDY, 22, 12);
    DrawGrid(_cEnemyGrid, ENEMYGRIDX, GRIDY, _bDebug);
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
void ShowSummary(bool _bWon, int _iPlayerShots, int _iPlayerHits, int _iEnemyShots, int _iEnemyHits)
{
    ClearScreen();
    PrintHeader();

    // blue wave under the title then white sides
    SetRgb(COLOUR_BLUE_ON_BLACK);
    DrawFrameLine(10, '~');
    SetRgb(COLOUR_WHITE_ON_BLACK);
    DrawFrameSides(11, 25);

    // victory or defeat
    if (_bWon)
    {
        SetRgb(COLOUR_GREEN_ON_BLACK);
        GotoXY(41, 13);
        cout << "*** VICTORY ***";
    }
    else
    {
        SetRgb(COLOUR_RED_ON_BLACK);
        GotoXY(41, 13);
        cout << "*** DEFEAT ***";
    }

    // shots hits and misses for both sides
    SetRgb(COLOUR_YELLOW_ON_BLACK);
    GotoXY(40, 16);
    cout << "You";
    GotoXY(54, 16);
    cout << "Enemy";

    SetRgb(COLOUR_WHITE_ON_BLACK);
    GotoXY(30, 17);
    cout << "Shots:";
    GotoXY(40, 17);
    cout << _iPlayerShots;
    GotoXY(54, 17);
    cout << _iEnemyShots;
    GotoXY(30, 18);
    cout << "Hits:";
    GotoXY(40, 18);
    cout << _iPlayerHits;
    GotoXY(54, 18);
    cout << _iEnemyHits;
    GotoXY(30, 19);
    cout << "Misses:";
    GotoXY(40, 19);
    cout << _iPlayerShots - _iPlayerHits;
    GotoXY(54, 19);
    cout << _iEnemyShots - _iEnemyHits;

    SetRgb(COLOUR_YELLOW_ON_BLACK);
    GotoXY(34, 23);
    cout << "Press enter to return to the menu";
    DrawFrameLine(26, '=');

    cin.get();
}

void ShowInstructions()
{
    ClearScreen();
    PrintHeader();

    // blue wave under the title then white sides
    SetRgb(COLOUR_BLUE_ON_BLACK);
    DrawFrameLine(10, '~');
    SetRgb(COLOUR_WHITE_ON_BLACK);
    DrawFrameSides(11, 25);

    GotoXY(40, 12);
    cout << "HOW TO PLAY";
    GotoXY(15, 14);
    cout << "Place your 5 ships on your grid (left), by hand or at random";
    GotoXY(15, 15);
    cout << "Ships are 5, 4, 3, 3 and 2 cells long and cannot overlap";
    GotoXY(15, 17);
    cout << "Manual placement: type a letter, a number and H or V, eg B7 H";
    GotoXY(15, 18);
    cout << "H runs the ship right from that cell, V runs it down";
    GotoXY(15, 20);
    cout << "Take turns firing at the enemy grid (right), eg B7";
    GotoXY(15, 21);
    cout << "X is a hit, ? is a miss, # is ocean, O is one of your ships";
    GotoXY(15, 22);
    cout << "Sink all 5 enemy ships before they sink yours to win";
    GotoXY(15, 24);
    cout << "Debug mode (menu option 5) shows the enemy ships";

    SetRgb(COLOUR_YELLOW_ON_BLACK);
    GotoXY(34, 25);
    cout << "Press enter to return to the menu";
    DrawFrameLine(26, '=');

    cin.get();
}

void ShowCredits()
{
    ClearScreen();
    PrintHeader();

    // blue wave under the title then white sides
    SetRgb(COLOUR_BLUE_ON_BLACK);
    DrawFrameLine(10, '~');
    SetRgb(COLOUR_WHITE_ON_BLACK);
    DrawFrameSides(11, 25);

    GotoXY(40, 13);
    cout << "CREDITS";
    GotoXY(15, 15);
    cout << "Game by Campbell Roberts";
    GotoXY(15, 16);
    cout << "Media Design School, GD1P01";
    GotoXY(15, 18);
    cout << "Title art: https://ascii.co.uk/art/battleships";
    GotoXY(15, 19);
    cout << "Submarine art: https://www.asciiart.eu/art/49d8fc2dbf033525";

    SetRgb(COLOUR_YELLOW_ON_BLACK);
    GotoXY(34, 25);
    cout << "Press enter to return to the menu";
    DrawFrameLine(26, '=');

    cin.get();
}