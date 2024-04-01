#pragma once
#define _WIN32_WINNT 0x0500

//Input and output format library
#include <iostream>
#include <iomanip>

// Game logic and algorithm library
#include <algorithm>
#include <cmath>
#include <vector>
#include <deque>

// For console settings
#include <windows.h>

struct BoardState{
    int row = 4; //default row
    int col = 6; //default column
    int** board; 
    char** poke; //display chararter on each cell
};