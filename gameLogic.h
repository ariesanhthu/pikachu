#include "lib.h"
#include "board.cpp"

// Finding the path between two cells
bool findPath(BoardState a, int x1, int x2, int y1, int y2, int line[][2]);

// Checking if there are any valid moves left
bool checkLegalMove(BoardState a, int &sugx1, int &sugy1, int &sugx2, int &sugy2);

// Level checking to call the below shifting function
void levelCheck(BoardState a, int x1, int y1, int x2, int y2, int lvl, int lvlcap[]);

// Shift-up function
void goUp(BoardState a, int x, int y, int m);

// Shift-down function
void goDown(BoardState a, int x, int y, int m);

// Shift-left function
void goLeft(BoardState a, int x, int y, int n);

// Shift-right function
void goRight(BoardState a, int x, int y, int n);

// Deleting memory used for nightmare array
void deleteNightmare(BoardState a, bool **&nightmare);

// Generate the nightmare array
void generateNightmare(BoardState a, bool **&nightmare);

// Randomize the hidden cells of the board
void resetNightmare(BoardState a, bool **nightmare);

// Calculate highscore
void calculateScore(PlayerState &player);
