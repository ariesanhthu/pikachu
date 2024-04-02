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

void printCell(int bgColor, int cellColor, int data, int x, int y, bool nmCheck, bool** nightmare){
    setColor(bgColor, cellColor);
    gotoXY(x * 3 + 2, y * 5 + 2);
    cout << "-----";
    gotoXY(x * 3 + 3, y * 5 + 2);
    if(nmCheck && nightmare[x][y])
        cout << "|   |";
    else
        cout << "| " << (char) data << " |";
    gotoXY(x * 3 + 4, y * 5 + 2);
    cout << "-----";
}

void clearCell(int color, BoardState a, int x, int y){
    setColor(color, 7);
    gotoXY(x * 3 + 2, y * 5 + 2);
    for(int i = 0; i < 5; i++)
        cout << a.display[x * 3][y * 5 + i];
	
    gotoXY(x * 3 + 3, y * 5 + 2);
    for(int i = 0; i < 5; i++)
        cout << a.display[x * 3 + 1][y * 5 + i];
	
    gotoXY(x * 3 + 4, y * 5 + 2);
    for(int i = 0; i < 5; i++)
        cout << a.display[x * 3 + 2][y * 5 + i];
}

void showBoard(BoardState a, int lvl, int curX, int curY, int &FcurX, int &FcurY, int &x1, int &y1, int &x2, int &y2, bool nmCheck, bool** nightmare, time_t suggtime, bool &endsugg, int sugx1, int sugy1, int sugx2, int sugy2, bool &newgame, bool &hint, bool &choose_1, bool &choose_2){
    showConsoleCursor(false);
    gotoXY(1, 0);
	
	// If this is newgame, print all cells of the board
    if(newgame)
    {
        setColor(0, 6);
        for (int i = 0; i <= a.col + 1; i++)
            cout << "####";
        cout << "####" << endl;
		
        gotoXY(3 * (a.row + 2) + 2, 0);
        for (int i = 0; i <= a.col + 1; i++)
            cout << "#####";
        cout << "####" << endl;

        for (int i = 0; i <= a.row + 1; i++){
            setColor(0, 6);
            for (int u = 0; u < 3; u++){
                gotoXY(i * 3 + 2 + u, 0);
                cout << "# ";
                gotoXY(i * 3 + 2 + u, 5 * (a.col + 2) + 2);
                cout << " #";
            }
            for (int j = 0; j <= a.col + 1; j++)
                if(a.board[i][j])
                    printCell(0, a.board[i][j] % 5 + 9, a.board[i][j], i, j, nmCheck, nightmare);
                else
                    clearCell(0, a, i, j);
        }
		
        if(a.board[curX][curY])
            printCell(8, 7, a.board[curX][curY], curX, curY, nmCheck, nightmare);
		
        else
            clearCell(8, a, curX, curY);
		
        newgame = false;
    }
	
	// If not, then
    else{
		
		//If the suggestion is out of time
        if(endsugg){
            if(!nmCheck){
                if(sugx1 == x1 && sugy1 == y1)
                    printCell(6, 14, a.board[sugx1][sugy1], sugx1, sugy1, nmCheck, nightmare);
                
				else
                    if(sugx1 == curX && sugy1 == curY)
                        printCell(8, 7, a.board[sugx1][sugy1], sugx1, sugy1, nmCheck, nightmare);
                    
					else
                        if(a.board[sugx1][sugy1])
                            printCell(0, a.board[sugx1][sugy1] % 5 + 9, a.board[sugx1][sugy1], sugx1, sugy1, nmCheck, nightmare);
                        
						else
                            clearCell(0, a, sugx1, sugy1);
                
				if(sugx2 == x1 && sugy2 == y1)
                    printCell(6, 14, a.board[sugx2][sugy2], sugx2, sugy2, nmCheck, nightmare);
                
				else
                    if(sugx2 == curX && sugy2 == curY)
                        printCell(8, 7, a.board[sugx2][sugy2], sugx2, sugy2, nmCheck, nightmare);
                    
					else
                        if(a.board[sugx2][sugy2])
                            printCell(0, a.board[sugx2][sugy2] % 5 + 9, a.board[sugx2][sugy2], sugx2, sugy2, nmCheck, nightmare);
                        
						else
                            clearCell(0, a, sugx2, sugy2);
            }
            endsugg = false;
        }
		
        if((FcurX != curX) || (FcurY != curY)){
            if(FcurX == x1 && FcurY == y1)
                printCell(6, 14, a.board[FcurX][FcurY], FcurX, FcurY, nmCheck, nightmare);
            
			else 
				if(!nmCheck && ((FcurX == sugx1 && FcurY == sugy1) || (FcurX == sugx2 && FcurY == sugy2)) && suggtime)
					printCell(a.board[FcurX][FcurY] % 5 + 1, a.board[FcurX][FcurY] % 5 + 9, a.board[FcurX][FcurY], FcurX, FcurY, nmCheck, nightmare);
            
				else 
					if(a.board[FcurX][FcurY])
						if(nmCheck && nightmare[FcurX][FcurY])
							printCell(0, 7, a.board[FcurX][FcurY], FcurX, FcurY, nmCheck, nightmare);
						else
							printCell(0, a.board[FcurX][FcurY] % 5 + 9, a.board[FcurX][FcurY], FcurX, FcurY, nmCheck, nightmare);
            
					else
						clearCell(0, a, FcurX, FcurY);
            
			if(curX == x1 && curY == y1)
                printCell(6, 14, a.board[curX][curY], curX, curY, nmCheck, nightmare);
            
			else 
				if(a.board[curX][curY])
					printCell(8, 7, a.board[curX][curY], curX, curY, nmCheck, nightmare);
            
				else
					clearCell(8, a, curX, curY);
            
			FcurX = curX;
            FcurY = curY;
        }
		
        else{
            if(choose_1){
                printCell(6, 14, a.board[x1][y1], x1, y1, nmCheck, nightmare);
                choose_1 = false;
            }
            if(hint){
                if(!nmCheck){
                    if(sugx1 != x1 || sugy1 != y1)
                        printCell(a.board[sugx1][sugy1] % 5 + 1, a.board[sugx1][sugy1] % 5 + 9, a.board[sugx1][sugy1], sugx1, sugy1, nmCheck, nightmare);
                    if(sugx2 != x1 || sugy2 != y1)
                        printCell(a.board[sugx2][sugy2] % 5 + 1, a.board[sugx2][sugy2] % 5 + 9, a.board[sugx2][sugy2], sugx2, sugy2, nmCheck, nightmare);
                }
                hint = false;
            }
            if(choose_2){
                if(a.board[x1][y1])
                    if(nmCheck && nightmare[x1][y1])
                        printCell(0, 7, a.board[x1][y1], x1, y1, nmCheck, nightmare);
                    else
                        printCell(0, a.board[x1][y1] % 5 + 9, a.board[x1][y1], x1, y1, nmCheck, nightmare);
                else
                    clearCell(0, a, x1, y1);
                if(a.board[x2][y2])
                    printCell(8, 7, a.board[x2][y2], x2, y2, nmCheck, nightmare);
                else
                    clearCell(8, a, x2, y2);
                x1 = 0, y1 = 0;
                x2 = 0, y2 = 0;
                choose_2 = false;
            }
        }
    }
}