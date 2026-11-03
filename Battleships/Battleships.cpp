/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer
File Name : Battleships.cpp
Description : main source file for console Battleships game
Author : Campbell Roberts
Mail : Campbell.Roberts@mds.ac.nz
**************************************************************************/
/*
TO DO LATER MAYBE:
Change ships from O to <=>/<==>/<===> etc
Total shots, Hit + miss counter
    int WINS = 0; in main unused, wins counter later or delete
*/

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;
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

// Constants.
const int SCREENWIDTH = 80; 
const int SCREENHEIGHT = 24;
const int GRIDSIZE = 10;
const int CELLWIDTH = 2;
const char OCEAN = '#';
const char HIT = 'X';
const char MISS = '?';
const char SHIP = 'O';
const int NUMSHIPS = 5;

// Functions.
void ClearScreen();
void GotoXY(int _iX, int _iY);
void SetRgb(EColour _eColour);
void DrawBox(int _iLeft, int _iTop, int _iWidth, int _iHeight);
void FillGrid(char _cGrid[GRIDSIZE][GRIDSIZE]);
void DrawGrid(char _cGrid[GRIDSIZE][GRIDSIZE], int _iLeft, int _iTop, bool _bShowShips);
void DrawLabels(int _iLeft, int _iTop);
bool PlaceShip(char _cGrid[GRIDSIZE][GRIDSIZE], int _iRow, int _iCol, int _iLength, bool _bHorizontal);
void AutoPlaceShips(char _cGrid[GRIDSIZE][GRIDSIZE]);
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


int main()
{
    int iMenuOption = 0;
    int WINS = 0;
    int MODE = 0;
    srand(static_cast<unsigned int>(time(0)));
    do {
        ClearScreen();
        PrintHeader();
        PrintAscii();
        SetRgb(COLOUR_WHITE_ON_BLACK);
        cout << R"(         |  _  |                                   ||                   =@=                |             
         | | | | Start:                            ||                   =@=                |
         |_____|                                   ||                .==+@+==.             |          
         |  _  |                                   ||                   :@-                |             
         | | | | Instructions:                     ||                   -@-                |             
         |_____|                                   ||                   -@=                |             
         |  _  |                                   ||                   =@=                |             
         | | | | Credits:                          ||            -@=    +@+    -@-         |      
         |_____|                                   ||             *%:  .%@%.  :%*          |       
         |  _  |                                   ||              .#@@@@@@@@@#:           |        
         | | | | Quit Game:                        ||                   =@+                |             
         |_____|                                   ||                                      |)" << endl;
        SetRgb(COLOUR_YELLOW_ON_BLACK);
        cout <<
            R"(         |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
         |                                                                                 |)" << endl;
        const int RIGHTBORDERX = 91;
        const int NUMBERX = 12;
        const int FIRSTNUMBERY = 13;
        const int NUMBERSPACING = 3;
        cout << "         |                            Please enter your choice: ";
        // get cursor pos right after the prompt.
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        COORD coordPrompt = csbi.dwCursorPosition;
        cout << "\n         |=================================================================================|";
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        coordPrompt.Y = csbi.dwCursorPosition.Y - 1;
        GotoXY(RIGHTBORDERX, coordPrompt.Y);
        cout << "|";

        SetRgb(COLOUR_RED_ON_BLACK);
        for (int iOption = 1; iOption <= 4; ++iOption)
        {
            GotoXY(NUMBERX, coordPrompt.Y - FIRSTNUMBERY + (iOption - 1) * NUMBERSPACING);
            cout << iOption;
        }
        //jump back to just after the prompt.
        GotoXY(coordPrompt.X, coordPrompt.Y);
        cin >> iMenuOption;

        //Input check
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input, please enter a number.\n" << endl;
            Sleep(1500);
            continue;
        }
        switch (iMenuOption) {
        case 1:
        {
            ClearScreen();

            char cPlayerGrid[GRIDSIZE][GRIDSIZE];
            char cEnemyGrid[GRIDSIZE][GRIDSIZE];
            FillGrid(cPlayerGrid);
            FillGrid(cEnemyGrid);
            AutoPlaceShips(cPlayerGrid);
            AutoPlaceShips(cEnemyGrid);

            //Playregrid (left)
            SetRgb(COLOUR_YELLOW_ON_BLACK);
            DrawBox(6, 4, 22, 12);
            DrawGrid(cPlayerGrid, 6, 4, true);
            DrawLabels(6, 4);

            // red middle bar |
            SetRgb(COLOUR_RED_ON_BLACK);
            for (int iY = 3; iY < 17; iY++)
            {
                GotoXY(31, iY);
                cout << "|";
            }

            //enemy grid (right)
            SetRgb(COLOUR_YELLOW_ON_BLACK);
            DrawBox(36, 4, 22, 12);
            DrawGrid(cEnemyGrid, 36, 4, false);
            DrawLabels(36, 4);
            // text under the grids
            SetRgb(COLOUR_RED_ON_BLACK);
            GotoXY(6, 17);
            cout << "You";
            GotoXY(36, 17);
            cout << "Enemy";

            SetRgb(COLOUR_WHITE_ON_BLACK);
            GotoXY(0, 20);
            system("pause");
            break;
        }
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        default:
            cout << "\nInvalid option, please choose 1 to 4.\n" << endl;
            Sleep(1500);
            break;
        }


    } while (iMenuOption != 4);
    return 0;
}

void GotoXY(int _iX, int _iY)
{
    COORD point;
    point.X = _iX;
    point.Y = _iY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void ClearScreen()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; 
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void SetRgb(EColour _eColour)
{
    switch (_eColour) // TF: Conditional Statement
    {
    case COLOUR_WHITE_ON_BLACK:
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    }
    case COLOUR_RED_ON_BLACK:
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED);
        break;
    }
    case COLOUR_GREEN_ON_BLACK:
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        break;
    }
    case COLOUR_YELLOW_ON_BLACK:
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    }
    case COLOUR_BLUE_ON_BLACK:
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        break;
    }
    default:
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    }
    }
}

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