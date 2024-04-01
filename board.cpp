#include "board.h"

//Deallocate board
void deleteMem(BoardState &a){
    for (int i = 0; i < a.row + 2; i++)
        delete[] a.board[i];
    delete[] a.board;
}

void generateBoard(BoardState &a) {
    a.board = new int* [a.row + 2];

    for (int i = 0; i < a.row + 2; i++) {
        a.board[i] = new int[a.col + 2];
        for (int j = 0; j < a.col + 2; j++)
            a.board[i][j] = 0;
    }

    int count = 0;
    char gen = 'A';

    while(true){
        if ((int) (gen - 'A' + 1) * 4 < a.row * a.col){
            for (int i = 1; (i <= 4) && (count <= a.row * a.col); ){
                int x = rand() % a.row + 1;
                int y = rand() % a.col + 1; 
                if (a.board[x][y] == 0){
                    i++;
                    a.board[x][y] = (int) gen;
                    count ++;
                }
            }
            gen++;
        }
        else {
            for (int i = 1; i <= a.row; i++)
                for (int j = 1; j <= a.col; j++)
                    if (a.board[i][j] == 0){
                        a.board[i][j] = (int) gen;
                        count++;
                    }
        }

        //Checking if all of the board is filled
        if (count >= a.row * a.col){
            break;
        }
    }

}