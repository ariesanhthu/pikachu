#include "board.h"

//Deallocate board
void deleteMem(BoardState &a){
    for (int i = 0; i < a.row + 2; i++)
        delete[] a.board[i];
    delete[] a.board;
}

/*
Idea:
    - Bảng sẽ tạo ra từ từ các kí tự bắt đầu từ 'A' cho đến khi mỗi kí tự đủ 4 lần
    - Mỗi kí tự sẽ được chuyển về 1-base. m Ví dụ 1 là A, 2 là B, ...
    - Để kí tự được sinh ra thì các kí tự trước đó đã được sinh ra. Chính vì thế nên điều kiện để được kí tự sinh ra là số đại diện cho kí tự đó nhân 4 phải bé hơn tổng số phần tử của mảng
    - Sau khi mỗi kí tự sinh ra để đủ 4 thì có thể còn dư từ 0 - 3 ô nên là sẽ có thêm đk thê có thể lắp đầy các ô thừa còn lại
    - Sau mỗi lần sinh ra sẽ có biến count để kiểm tra số phần tử, nếu count đủ bằng số lượng phần tử thì sẽ break vòng lặp 
*/
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