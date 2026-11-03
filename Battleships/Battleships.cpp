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

/*
         |=================================================================================|
         |                _           _   _   _           _     _                          |
         |               | |         | | | | | |         | |   (_)                         |
         |               | |__   __ _| |_| |_| | ___  ___| |__  _ _ __  ___                |
         |               | '_ \ / _` | __| __| |/ _ \/ __| '_ \| | '_ \/ __|               |
         |               | |_) | (_| | |_| |_| |  __/\__ \ | | | | |_) \__ \               |
         |               |_.__/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/|___/               |
         |                                                     | |                         |
         |                                                     |_|                         |
         |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
         |                                                                                 |
         |                 A B C D E F G H I J     |     A B C D E F G H I J               |
         |                ----------------------   |    ----------------------             |
         |             1  |# # # # # # # # # # |   | 1  |# # # # # # # # # # |             |
         |             2  |# # # # # # # # # # |   | 2  |# # # # # # # # # # |             |
         |             3  |# # # # # # # # # # |   | 3  |# # # # # # # # # # |             |
         |             4  |# # # # # # # # # # |   | 4  |# # # # # # # # # # |             |
         |             5  |# # # # # # # # # # |   | 5  |# # # # # # # # # # |             |
         |             6  |# # # # # # # # # # |   | 6  |# # # # # # # # # # |             |
         |             7  |# # # # # # # # # # |   | 7  |# # # # # # # # # # |             |
         |             8  |# # # # # # # # # # |   | 8  |# # # # # # # # # # |             |
         |             9  |# # # # # # # # # # |   | 9  |# # # # # # # # # # |             |
         |             10 |# # # # # # # # # # |   | 10 |# # # # # # # # # # |             |
         |                ----------------------   |    ----------------------             |
         |                --You--                  |     --Enemy--                         |
         |                Shots:                   |     Shots:                            |
         |                Hits:                    |     Hits:                             |
         |                Misses:                  |     Misses:                           |
         |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
         |  _  |                                   |  _  |                                 |
         | |1| | Manual Ship Placement:            | |2| | Auto Ship Placement:            |
         |_____|                                   |_____|                                 |
         |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
         |                                                                                 |
         |                            Please enter your choice:                            |
         |=================================================================================|




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
const int FRAMELEFTX = 9;
const int FRAMERIGHTX = 91;
const int DIVIDERX = 50;
const int PLAYERGRIDX = 21;
const int ENEMYGRIDX = 61;
const int GRIDY = 13;
const int PLACEMANUALX = 15;
const int PLACEAUTOX = 57;

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
void DrawFrameLine(int _iY, char _cFill);
void DrawFrameSides(int _iTop, int _iBottom);
void DrawPlayScreen(char _cPlayerGrid[GRIDSIZE][GRIDSIZE], char _cEnemyGrid[GRIDSIZE][GRIDSIZE]);
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
    int iWins = 0;
    int iMode = 0;
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
            ///AutoPlaceShips(cPlayerGrid);
            AutoPlaceShips(cEnemyGrid);


            DrawPlayScreen(cPlayerGrid, cEnemyGrid);
            cin >> iMode;

            if (iMode == 2)
            {
                AutoPlaceShips(cPlayerGrid);
            }
            else if (iMode == 1)
            {
                // manual placement goes here later
            }
            else
            {
                // input, do later
            }
           
            SetRgb(COLOUR_YELLOW_ON_BLACK);
            DrawGrid(cPlayerGrid, PLAYERGRIDX, GRIDY, true);
            SetRgb(COLOUR_WHITE_ON_BLACK);
            GotoXY(0, 38);
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