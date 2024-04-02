#include "lib.h"
#include "consoleSetting.cpp"

//Login section
void login(PlayerState &player, BoardState &a, int &mCurX, int &menu, int &playerid, bool &succlog, int lvlcap[], time_t &oriTime);

//Checking if login request is valid
void checkLogin(PlayerState player, int &playerid, bool &succ, int &submenu);

//Checking if register request is valid
void checkRegis(PlayerState &player, int &playerid, bool &succ, int &submenu, bool &log);

//For saving the game and players' data
void saveGame(PlayerState player, int playerid, BoardState a);

//Loading save date
void loadGame(PlayerState &player, int playerid, BoardState &a, int lvlcap[], time_t &oriTime);

//Loading leaderboard
void loadLB(LeaderBoard &lb);

//Updating leaderboard
void updateLB(LeaderBoard &lb, PlayerState player);
