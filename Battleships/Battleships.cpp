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
#include "Constants.h"
#include "Console.h"
#include "Grid.h"
#include "Screens.h"
#include "Input.h"
using namespace std;
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
                ManualPlaceShips(cPlayerGrid);
            }
            else
            {
                // input, do later
            }

            SetRgb(COLOUR_YELLOW_ON_BLACK);
            DrawGrid(cPlayerGrid, PLAYERGRIDX, GRIDY, true);
            ClearPlacementBoxes();

            int iPlayerShots = 0;
            int iPlayerHits = 0;
            int iPlayerMisses = 0;
            int iEnemyShots = 0;
            int iEnemyHits = 0;
            int iEnemyMisses = 0;

            // keep taking turns until one side has no ships left
            while (HasShips(cPlayerGrid) && HasShips(cEnemyGrid))
            {
                // player turn
                int iRow = 0;
                int iCol = 0;
                ShowPrompt("Fire at the enemy grid, eg B7", "Enter your target: ");

                if (ReadTarget(iRow, iCol))
                {
                    EShotResult eResult = FireShot(cEnemyGrid[iRow][iCol]);

                    if (eResult == SHOT_REPEAT)
                    {
                        ShowPrompt("You already fired there, try again");
                        Sleep(1500);
                    }
                    else
                    {
                        ++iPlayerShots;
                        if (eResult == SHOT_HIT)
                        {
                            ++iPlayerHits;
                            ShowPrompt("Hit!");
                        }
                        else
                        {
                            ++iPlayerMisses;
                            ShowPrompt("Miss");
                        }
                        DrawGrid(cEnemyGrid, ENEMYGRIDX, GRIDY, false);
                        DrawStats(PLAYERGRIDX + 7, iPlayerShots, iPlayerHits, iPlayerMisses);
                        Sleep(900);

                        // enemy turn, only if player didnt just win
                        if (HasShips(cEnemyGrid))
                        {
                            int iEnemyRow = 0;
                            int iEnemyCol = 0;
                            EShotResult eEnemyResult = ComputerShoot(cPlayerGrid, iEnemyRow, iEnemyCol);

                            ++iEnemyShots;
                            if (eEnemyResult == SHOT_HIT)
                            {
                                ++iEnemyHits;
                                ShowPrompt(string("Enemy fired at ") + char('A' + iEnemyCol) + to_string(iEnemyRow + 1) + ": Hit!");
                            }
                            else
                            {
                                ++iEnemyMisses;
                                ShowPrompt(string("Enemy fired at ") + char('A' + iEnemyCol) + to_string(iEnemyRow + 1) + ": Miss");
                            }
                            DrawGrid(cPlayerGrid, PLAYERGRIDX, GRIDY, true);
                            DrawStats(ENEMYGRIDX + 6, iEnemyShots, iEnemyHits, iEnemyMisses);
                            Sleep(1500);
                        }
                    }
                }
                else
                {
                    ShowPrompt("Invalid input, eg B7");
                    Sleep(1500);
                }
            }

            // whoever still has ships won
            if (HasShips(cPlayerGrid))
            {
                ShowPrompt("VICTORY, you sank the enemy fleet!");
            }
            else
            {
                ShowPrompt("DEFEAT, the enemy sank your fleet!");
            }
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
