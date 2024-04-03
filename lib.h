#pragma once
#define _WIN32_WINNT 0x0500 // This is using windows.h without errors
// For the input and output format
#include <iostream>
#include <iomanip>

// Time feature library
#include <ctime>

// Bulding player struct
#include <cstring>
#include <string>

// For convenient use during the BFS 
#include <vector>
#include <deque>

// Algorithm and game logic library
#include <cmath>
#include <algorithm>

// COnsole setting library
#include <windows.h>

// File library
#include <fstream>
#include <stdio.h>

// Library for keyboard input
#include <conio.h>
#include <stdlib.h>

// Music feature library 
#include <mmsystem.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_ESCAPE 27
#define KEY_HELP 104
#define KEY_SUFFLE 114

//Board structure
struct BoardState{
    int row = 4, col = 6;
    int** board;
    char** display;
};

//Player and save structure 
struct PlayerState{
    char username[32] = "";
    char password[32] = "";
    int mode = 0;
    int lvl = 1;
    int lvlstate = 1;
    int count = 24;
    int timeleft = 220;
    int score = 0;
};

//Leaderboard structure
struct LeaderBoard{
    int hsEasy[5] = {};
    char userEasy[5][32] = {};
    int hsMedium[5] = {};
    char userMedium[5][32] = {};
    int hsHard[5] = {};
    char userHard[5][32] = {};
    int hsNightmare[5] = {};
    char userNightmare[5][32] = {};
};