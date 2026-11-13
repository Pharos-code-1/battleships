/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer
File Name : Console.cpp
Description : colour, cursor, clear screen and window size functions
Author : Campbell Roberts
Mail : Campbell.Roberts@mds.ac.nz
**************************************************************************/
#include <iostream>
#include "Console.h"

using namespace std;

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

    // wipe the scrollback too
    std::cout << "\033[3J" << flush;

    // scroll view back to the top
    SMALL_RECT srWindow;
    srWindow.Left = 0;
    srWindow.Top = 0;
    srWindow.Right = csbi.srWindow.Right - csbi.srWindow.Left;
    srWindow.Bottom = csbi.srWindow.Bottom - csbi.srWindow.Top;
    SetConsoleWindowInfo(hConsole, TRUE, &srWindow);
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
int GetWindowHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void MakeFullscreen(int _iRows)
{
    // only press alt enter if the window is too short
    if (GetWindowHeight() < _iRows)
    {
        keybd_event(VK_MENU, 0, 0, 0);
        keybd_event(VK_RETURN, 0, 0, 0);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);

        // give the window a moment to change size
        Sleep(500);
    }
}

void WaitForWindowHeight(int _iRows)
{
    bool bWarned = false;

    // wait until the window is tall enough
    while (GetWindowHeight() < _iRows)
    {
        if (!bWarned)
        {
            ClearScreen();
            SetRgb(COLOUR_WHITE_ON_BLACK);
            cout << "Window too small, maximise it to continue" << endl;
            bWarned = true;
        }
        Sleep(300);
    }
}