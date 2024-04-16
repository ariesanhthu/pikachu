#include "board.h"

void generateBoard(headerList *&board, int col, int row, int lvl){
    int countLeft[26];
    for (int i = 0; i < 26; i++)
        countLeft[i] = 4;
    int cnt = 0;
    int cap = row * col / 4;
    board = nullptr;
    int _col, _row;
    if (lvl <= 3){
        _col = col;
        _row = row;
    }
    else{
        _col = row;
        _row = col;
    }
    for (int i = 0; i < _row;){
        node * head = nullptr;
        for (int j = 0; j < _col;){
            int gen = rand() % cap + 65;
            if (countLeft[gen - 65] != 0){
                addNode(head, gen, j);
                countLeft[gen - 65] -= 1;
            }
        }
        addHeader(board, head, i);
        traceH(board, i)->size = _col;
    }
}

void showBoard(headerList *board, int col, int row, int lvl){
    for (int i = 0; i <= col; i++)
        cout << i << " ";
    for (int i = 1; i <= row; i++)
        cout << endl << i;
    /////////////////////////////////////
    int _row, _col; 
    if (lvl <= 3)
    {
        _row = row;
        _col = col;
    }
    else 
    {
        _row = col;
        _col = row;
    }
    for (int i = 1; i <= _row ; i++)
    {
        bool flag = true;
        for (int j = 1; j <= _col; j++)
        {   
            if (lvl <= 2)
                gotoxy(i, 2 * j);
            else if (lvl == 3)
                gotoxy(i, 2 * (_col - j + 1));
            else if (lvl == 4)
                gotoxy(j, 2 * i);
            else 
                gotoxy(_col - j + 1, 2 * i);

            if (flag)
            {
                if (traceH(board, i)->head != nullptr && trace(traceH(board, i)->head, j) != nullptr)
                {   
                    cout << ((trace(traceH(board, i)->head, j)->key != 0) ? (char) trace(traceH(board, i)->head, j)->key : '.') << ' ';
                }
                else{
                    flag = false;
                    cout << ". ";
                }
            }
            else
            {
                cout << ". ";
            }
        }
    }
}