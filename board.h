#include "lib.h"
#include "consoleSetting.h"

//Delete memory of a board
void deleteMem(BoardState &a);

//Generating board
void generateBoard(BoardState &a);

//Print each cells
void printCell(int bColor, int cellColor, int data, int x, int y);

//Clear certain cells
void clearCell(int color, BoardState a, int x, int y);

//Show the entire board
void showBoard(BoardState a, int lvl, int curX, int curY, int &FcurX, int &FcurY, int &x1, int &y1, int &x2, int &y2, time_t suggtime, bool &endsugg, int sugx1, int sugy1, int sugx2, int sugy2, bool &newgame, bool &hint, bool &choose_1, bool &choose_2);

//Reset board if there is no valid move
void resetBoard(BoardState a);

//Generating background
void generateArt(BoardState &a);

//Deleting background
void deleteArt(BoardState &a);

//Drawing line matching two cells
void drawLine(int line[][2]);

//Clear that line
void clearLine(int line[][2], BoardState a);