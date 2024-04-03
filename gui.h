#include "lib.h"
#include "consoleSetting.cpp"

// Generate the menu
void generateMenu(LeaderBoard lb, int &mode, int &row, int &col, int &menu, int &mCurX, bool &succlog, bool &cont, int &lvl);

// Print the menu
void printMenu(LeaderBoard lb, int row, int col, int menu, int mCurX);

/*
 menu = 1: main menu
        2: choose gamemode
        3: custom gamemode
        4, 5: in gameplay
        6: leaderboard
        7: pause
        8: continue
        0: out
*/

// receive keyboard input
void keyboardSelect(BoardState &a, int &curX, int &curY, int &x1, int &y1, int &x2, int &y2, int &menu, time_t &suggtime, time_t &timeleft, bool &hint, bool &choose_1, bool &choose_2, bool &suffle);

// Reset the current game board
void resetGame(BoardState a, int &count, int lvl, int lvlcap[], int &curX, int &curY, int &FcurX, int &FcurY);

// Reset the initialization for the attributes of the game
void eraseGame(PlayerState &player, BoardState &a, int lvlcap[]);

// Countdown function
void showTime(int &timeleft, time_t oriTime, int &menu, bool &eot, int score, time_t &suggtime, BoardState a, bool &endsugg);

void printLogo();