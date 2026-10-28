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

int main()
{
    //Test start for future code
    //https://www.asciiart.eu/art/49d8fc2dbf033525 + https://ascii.co.uk/art/battleships

	int MENUOPTION = 0;
	cout << "=======================================================================================\n";
	cout << "					 _           _   _   _           _     _							\n"
	cout << "					| |         | | | | | |         | |   (_)							\n"        
	cout << "					| |__   __ _| |_| |_| | ___  ___| |__  _ _ __  ___					\n"
	cout << "					| '_ \ / _` | __| __| |/ _ \/ __| '_ \| | '_ \/ __|					\n"
	cout << "					| |_) | (_| | |_| |_| |  __/\__ \ | | | | |_) \__ \					\n"
	cout << "					|_.__/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/|___/					\n"
	cout << "									                      | |							\n"
	cout << "						                          |#=)    |_|							\n"
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~oo~~~~~~~~~~~~~|#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
	cout << "                                 o o			  |#							    	\n"
	cout << "                                o ooo			  |#							    	\n"
	cout << "                                  o oo			  |#							        \n"
	cout << "                                     o o      |  |#									\n"
	cout << "                                      oo     _|__|#_									\n"
	cout << "                                        o   |   /   |									\n"
	cout << "   __                    ___________________|   \___|_________________					\n"
	cout << "  |   -_______-----------                                              \				\n"
	cout << " >|    _____                    >>>>         >>>>           >>>>        )				\n"
	cout << "  |__ -     ---------_________________________________________________ /				\n"
	cout << "																					    \n"
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
	cout << "Enter your choice: ";
    srand(static_cast <unsigned> (time(0)));

    int balance = 2000;
    int menuoption = 0;
    int mode = 0;
    int bet = 0;

    do {
        cout << "Player's chips: $" << balance << endl;
        cout << "1) Play Slots" << endl;
        cout << "2) Credits" << endl;
        cout << "3) Quit Game" << endl;
        cout << "Enter your choice: ";
        cin >> menuoption;

        //Input check
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input, please enter a number.\n" << endl;
            continue;
        }

        switch (menuoption) {
            // Choice 1 (of Main Menu) - Play slots
        case 1: {
            // Loop the slots menu so an invalid choice redisplays it
            bool backToMain = false;
            do {
                cout << "\nPlayer's chips: $" << balance << endl;
                cout << "1) Normal Slots" << endl;
                cout << "2) Jackpot Slots" << endl;
                cout << "3) See Multipliers" << endl;
                cout << "4) Back" << endl;
                cout << "Enter your choice: ";
                cin >> mode;

                //Input check
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\nInvalid input, please enter a number.\n" << endl;
                    continue;
                }

                switch (mode) {
                    //Choice 1 (of Play Slots) - Normal slots
                case 1: {
                    //Stop user playing when they don't have enough for the minimum bet
                    if (balance < 1) {
                        cout << "\nYou don't have enough chips to play Normal Slots.\n" << endl;
                        break;
                    }

                    cout << "\nNormal Slots selected." << endl;
                    cout << "Enter Bet amount, Minimum 1$ : ";
                    cin >> bet;
                    //Bet input check (Above 1, below balance)
                    while (cin.fail() || bet < 1 || bet > balance) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "\nInvalid bet. Enter bet amount (1-" << balance << "): ";
                        cin >> bet;
                    }
                    balance = (balance - bet);

                    //Generate 3 random numbers in range 2-7
                    int slotnum[3] = {
                       (rand() % 6) + 2,
                       (rand() % 6) + 2,
                       (rand() % 6) + 2
                    };
                    //Print Slot Machine Ascii with the random array values
                    cout << "\nBet amount: $" << bet
                        << "\n==============="
                        << "\n=-------------="
                        << "\n|=  " << slotnum[0] << "  " << slotnum[1] << "  " << slotnum[2] << "  =|"
                        << "\n===0===0===0==="
                        << "\n=-------------=\n" << endl;

                    // Normal Slots mode rewards
                    //Check if all numbers are =
                    if (slotnum[0] == slotnum[1] && slotnum[1] == slotnum[2]) {
                        //Check if they = 7
                        if (slotnum[0] == 7) {
                            cout << "All equal, all 7! 10x win!\n" << endl;
                            balance += bet * 10;
                        }
                        else {
                            cout << "All equal, not 7. 5x win!\n" << endl;
                            balance += bet * 5;
                        }
                    }
                    //Check If 2 numbers are =
                    else if (slotnum[0] == slotnum[1] || slotnum[1] == slotnum[2] || slotnum[0] == slotnum[2]) {
                        cout << "2 of 3 match! 3x win.\n" << endl;
                        balance += bet * 3;
                    }
                    else {
                        cout << "No match. Player loses bet.\n" << endl;
                    }

                    break;
                }
                      //Choice 2 (of Play Slots) - Jackpot slots
                case 2: {
                    //Stop user playing when they don't have enough for the minimum bet
                    if (balance < 100) {
                        cout << "\nYou don't have enough chips to play Jackpot Slots (minimum $100).\n" << endl;
                        break;
                    }

                    cout << "\nJackpot Slots selected." << endl;
                    cout << "Enter Bet amount, Minimum 100$ : ";
                    cin >> bet;

                    while (cin.fail() || bet < 100 || bet > balance) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid bet. Enter bet amount (100-" << balance << "): ";
                        cin >> bet;
                    }
                    balance = (balance - bet);


                    //Generate 7 random numbers in range 2-7, store in array 
                    int slotnum[7] = {
                       (rand() % 6) + 2,
                       (rand() % 6) + 2,
                       (rand() % 6) + 2,
                       (rand() % 6) + 2,
                       (rand() % 6) + 2,
                       (rand() % 6) + 2,
                       (rand() % 6) + 2
                    };


                    //Count how many times each number (2-7) appears
                    int count[8] = {
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0
                    };
                    for (int i = 0; i < 7; i++) {
                        count[slotnum[i]] = count[slotnum[i]] + 1;
                    }

                    //find highest count/which number 
                    int bestNum = 0;
                    int bestCount = 0;
                    for (int n = 2; n <= 7; n++) {
                        if (count[n] > bestCount) {
                            bestCount = count[n];
                            bestNum = n;
                        }
                    }
                    //Print Jackpot Slot Machine Ascii with the random array values
                    cout << "\nBet amount: $" << bet
                        << "\n============JACKPOT============"
                        << "\n===-------------------------==="
                        << "\n[==|  " << slotnum[0] << "  " << slotnum[1] << "  " << slotnum[2] << "  " << slotnum[3] << "  " << slotnum[4] << "  " << slotnum[5] << "  " << slotnum[6] << "  |==]"
                        << "\n===0===0===0===0===0===0===0==="
                        << "\n===-------------------------===\n" << endl;

                    //Jackpot Slots mode rewards
                    if (bestCount == 7 && bestNum == 7) {
                        cout << "All 7 are 7! MEGA JACKPOT! 100x win!\n" << endl;
                        balance += bet * 100;
                    }
                    else if (bestCount == 7) {
                        cout << "All 7 equal, not 7. 50x win!\n" << endl;
                        balance += bet * 50;
                    }
                    else if (bestCount == 6) {
                        cout << "6 of 7 match! 20x win!\n" << endl;
                        balance += bet * 20;
                    }
                    else if (bestCount == 5) {
                        cout << "5 of 7 match! 10x win!\n" << endl;
                        balance += bet * 10;
                    }
                    else if (bestCount == 4) {
                        cout << "4 of 7 match! 5x win!\n" << endl;
                        balance += bet * 5;
                    }
                    else {
                        cout << "No match. Player loses bet.\n" << endl;
                    }
                    break;
                }
                      //Choice 3 (of Play Slots) -  See Multipliers
                case 3:
                    cout << "\nMultiplier list:"
                        << "\n=============================="
                        << "\nNormal Slots:"
                        << "\n------------------------------"
                        << "\nNo numbers match: No reward - Player Loses bet\n2 out of 3 Numbers match: 3x Bet Amount\n3 out of 3 Numbers match: 5x Bet Amount\n3 out of 3 Numbers are 7: 10x Bet Amount"
                        << "\n=============================="
                        << "\nJackpot Slots:"
                        << "\n------------------------------"
                        << "\nBelow 4 out of 7 numbers match: No reward - Player Loses bet.\n4 out of 7 Numbers match: 5x Bet Amount\n5 out of 7 Numbers match: 10x Bet Amount\n6 out of 7 Numbers match: 20x Bet Amount\n7 out of 7 Numbers match: 50x Bet Amount\n7 out of 7 Numbers are 7: JACKPOT!!! - 100x Bet Amount\n" << endl;
                    break;
                    //Choice 4 (of Play Slots) -  Back
                case 4:
                    backToMain = true; //tell outer loop to return to the main menu
                    break;
                default:
                    cout << "Invalid choice, please try again." << endl;
                    break;
                }
            } while (!backToMain); //makes loop stay in the slots menu so you can play again until back is chosen
            break;
        }
              //Choice 2 (of Main Menu) - Credits
        case 2:
            cout << "                                                                _\n"
                << "                                                                \\`*-.\n"
                << "                                                                 )  _`-.\n"
                << "                                                                .  : `. .\n"
                << "                                                                : _   '  \\\n"
                << "                                                                ; *` _.   `*-._\n"
                << "                                                                `-.-'          `-.\n"
                << "                                                                  ;       `       `.\n"
                << "                                                                  :.       .        \\\n"
                << "                                                                  . \\  .   :   .-'   .\n"
                << "                                                                  '  `+.;  ;  '      :\n"
                << "                                                                  :  '  |    ;       ;-.\n"
                << "                                                                  ; '   : :`-:     _.`* ;\n"
                << "[This is a slot machine game created for GD1P01 by Campbell.R] .*' /  .*' ; .*`- +'  `*'\n"
                << "[                  Thank you for playing!                    ] `*-*   `*-*  `*-*'\n" << endl;
            //Not my Ascii art - https://www.asciiart.eu/art/40e94553cf590a1d


            break;
            //Choice 3 (of Main Menu) - Quit Game
        case 3:
            cout << "Thanks for playing!" << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }

    } while (menuoption != 3);
























				
	// End of test
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