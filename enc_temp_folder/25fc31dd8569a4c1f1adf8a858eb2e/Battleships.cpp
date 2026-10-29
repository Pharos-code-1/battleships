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

#include <iostream>
#include <windows.h>
using namespace std;
// Colour options for console text.
enum EColour
{
    COLOUR_WHITE_ON_BLACK = 0, // White on Black.
    COLOUR_RED_ON_BLACK = 1, // Red on Black.
    COLOUR_GREEN_ON_BLACK = 2, // Green on Black.
    COLOUR_YELLOW_ON_BLACK = 3, // Yellow on Black.
    COLOUR_BLUE_ON_BLACK = 4, // Blue on Black.
    COLOUR_MAGENTA_ON_BLACK = 5, // Magenta on Black.
    COLOUR_CYAN_ON_BLACK = 6, // Cyan on Black.
    COLOUR_BLACK_ON_GRAY = 7, // Black on Gray.
    COLOUR_BLACK_ON_WHITE = 8, // Black on White.
    COLOUR_RED_ON_WHITE = 9, // Red on White.
    COLOUR_GREEN_ON_WHITE = 10, // Green on White.
    COLOUR_YELLOW_ON_WHITE = 11, // Yellow on White.
    COLOUR_BLUE_ON_WHITE = 12, // Blue on White.
    COLOUR_MAGENTA_ON_WHITE = 13, // Magenta on White.
    COLOUR_CYAN_ON_WHITE = 14, // Cyan on White.
    COLOUR_WHITE_ON_WHITE = 15 // White on White.
};

// Constants.
const int SCREENWIDTH = 80; // TF: Constant
const int SCREENHEIGHT = 24;
const int GRIDSIZE = 10;
const int CELLWIDTH = 2;
const char OCEAN = '#';
const char HIT = 'X';
const char MISS = '?';
const char SHIP = 'O';

// Function Prototypes.
void ClearScreen();
void GotoXY(int _iX, int _iY);
void SetRgb(EColour _eColour);
void DrawBox(int _iLeft, int _iTop, int _iWidth, int _iHeight);
void FillGrid(char _cGrid[GRIDSIZE][GRIDSIZE]);
void DrawGrid(char _cGrid[GRIDSIZE][GRIDSIZE], int _iLeft, int _iTop);
void PrintAscii() {
    cout << R"(
         |=================================================================================|
         |                _           _   _   _           _     _                          |
         |               | |         | | | | | |         | |   (_)                         |
         |               | |__   __ _| |_| |_| | ___  ___| |__  _ _ __  ___                |
         |               | '_ \ / _` | __| __| |/ _ \/ __| '_ \| | '_ \/ __|               |
         |               | |_) | (_| | |_| |_| |  __/\__ \ | | | | |_) \__ \               |
         |               |_.__/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/|___/               |
         |                                                      | |                        |
         |                                                 |#)  |_|                        | 
         |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~oo~~~~~~~~~~~~~|#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
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
}       //https://ascii.co.uk/art/battleships + https://www.asciiart.eu/art/49d8fc2dbf033525
int main()
{
    int MENUOPTION = 0;
    int WINS = 0;
    int MODE = 0;
    PrintAscii();//(               )
    cout << R"(         |  _  |                                   ||                   =@=                |             
         | |1| | Start:                            ||                   =@=                |
         |_____|                                   ||                .==+@+==.             |          
         |  _  |                                   ||                   :@-                |             
         | |2| | Instructions:                     ||                   -@-                |             
         |_____|                                   ||                   -@=                |             
         |  _  |                                   ||                   =@=                |             
         | |3| | Credits:                          ||            -@=    +@+    -@-         |      
         |_____|                                   ||             *%:  .%@%.  :%*          |       
         |  _  |                                   ||              .#@@@@@@@@@#:           |        
         | |4| | Quit Game:                        ||                   =@+                |             
         |_____|                                   ||                                      |
         |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
         |                                                                                 |)" << endl; 
        cout << "         |       Please enter your choice: ";
        cin >> MENUOPTION;

        do {
        //Input check
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input, please enter a number.\n" << endl;
            continue;
        }
            switch (MENUOPTION) {
            case 1:
                ClearScreen();

                char cPlayerGrid[GRIDSIZE][GRIDSIZE]; // TF: Array

                FillGrid(cPlayerGrid);
                cPlayerGrid[0][0] = HIT;
                cPlayerGrid[0][1] = SHIP;
                cPlayerGrid[3][1] = MISS;

                SetRgb(COLOUR_YELLOW_ON_BLACK);
                DrawBox(2, 2, 22, 12);
                DrawGrid(cPlayerGrid, 2, 2);

                SetRgb(COLOUR_WHITE_ON_BLACK);
                GotoXY(0, 16);
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
               
                break;
            default:
                
                break;
            }
    

        } while (MENUOPTION != 4);
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
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; // TF: Arithmetic Operator
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
    for (int iX = 0; iX < _iWidth; ++iX) // TF: Iteration Structure
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

void DrawGrid(char _cGrid[GRIDSIZE][GRIDSIZE], int _iLeft, int _iTop)
{
    for (int iRow = 0; iRow < GRIDSIZE; ++iRow)
    {
        for (int iCol = 0; iCol < GRIDSIZE; ++iCol)
        {
            // Choose a colour based on what is in this cell.
            switch (_cGrid[iRow][iCol])
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
            default:
            {
                SetRgb(COLOUR_WHITE_ON_BLACK);
                break;
            }
            }

            // Move to this cell's position and print it two characters wide.
            GotoXY(_iLeft + 1 + (iCol * CELLWIDTH), _iTop + 1 + iRow);
            cout << _cGrid[iRow][iCol] << " ";
        }
    }

    SetRgb(COLOUR_WHITE_ON_BLACK);
}
