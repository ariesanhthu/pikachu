#include <bits/stdc++.h>
#include "linkedList.cpp"

// Finding a path between two cells
bool findPath(headerList * head, int row, int col, int x1, int x2, int y1, int y2);

// Check if there is any legal moves left 
bool checkLegalMove(headerList *board, int row, int col, int lvl);