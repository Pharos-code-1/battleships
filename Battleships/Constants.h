/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer
File Name : Constants.h
Description : main source file for console Battleships game
Author : Campbell Roberts
Mail : Campbell.Roberts@mds.ac.nz
**************************************************************************/
#pragma once
#include <string>
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
const int PROMPTX = 38;
const int PROMPTLINEY = 34;
const int PROMPTY = 35;
const int SHIPLENGTHS[NUMSHIPS] = { 5, 4, 3, 3, 2 };
const std::string SHIPNAMES[NUMSHIPS] = { "Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat" };