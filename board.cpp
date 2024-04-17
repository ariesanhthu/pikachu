#include "board.h"

//Deallocate board
void deleteMem(BoardState &a){
    for (int i = 0; i < a.row + 2; i++)
        delete[] a.board[i];
    delete[] a.board;
}

// Create element for board
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

void printCell(int bgColor, int cellColor, int data, int x, int y){
    SetColor(bgColor, cellColor);
    gotoxy(x * 3 + 2, y * 5 + 2);
    cout << "-----";
    gotoxy(x * 3 + 3, y * 5 + 2);
    cout << "| " << (char) data << " |";
    gotoxy(x * 3 + 4, y * 5 + 2);
    cout << "-----";
}

void clearCell(int color, BoardState a, int x, int y){
    SetColor(color, 7);
    gotoxy(x * 3 + 2, y * 5 + 2);
    for(int i = 0; i < 5; i++)
        cout << a.display[x * 3][y * 5 + i];
	
    gotoxy(x * 3 + 3, y * 5 + 2);
    for(int i = 0; i < 5; i++)
        cout << a.display[x * 3 + 1][y * 5 + i];
	
    gotoxy(x * 3 + 4, y * 5 + 2);
    for(int i = 0; i < 5; i++)
        cout << a.display[x * 3 + 2][y * 5 + i];
}

void showBoard(BoardState a, int lvl, int curX, int curY, int &FcurX, int &FcurY, int &x1, int &y1, int &x2, int &y2, time_t suggtime, bool &endsugg, int sugx1, int sugy1, int sugx2, int sugy2, bool &newgame, bool &hint, bool &choose_1, bool &choose_2){
    ShowConsoleCursor(false);
    gotoxy(1, 0);
	
	// If this is newgame, print all cells of the board
    if(newgame)
    {
        SetColor(0, 6);
        for (int i = 0; i <= a.col + 1; i++)
            cout << "#####";
        cout << "####" << endl;
		
        gotoxy(3 * (a.row + 2) + 2, 0);
        for (int i = 0; i <= a.col + 1; i++)
            cout << "#####";
        cout << "####" << endl;

        for (int i = 0; i <= a.row + 1; i++){
            SetColor(0, 6);
            for (int u = 0; u < 3; u++){
                gotoxy(i * 3 + 2 + u, 0);
                cout << "# ";
                gotoxy(i * 3 + 2 + u, 5 * (a.col + 2) + 2);
                cout << " #";
            }
            for (int j = 0; j <= a.col + 1; j++)
                if(a.board[i][j])
                    printCell(0, a.board[i][j] % 6 + 9, a.board[i][j], i, j);
                else
                    clearCell(0, a, i, j);
        }
		
        if(a.board[curX][curY])
            printCell(8, 7, a.board[curX][curY], curX, curY);
		
        else
            clearCell(8, a, curX, curY);
		
        newgame = false;
    }
	
	// If not, then
    else{
		
		//If the suggestion is out of time
        if(endsugg){
            if(sugx1 == x1 && sugy1 == y1)
                printCell(6, 14, a.board[sugx1][sugy1], sugx1, sugy1);
            
            else
                if(sugx1 == curX && sugy1 == curY)
                    printCell(8, 7, a.board[sugx1][sugy1], sugx1, sugy1);
                
                else
                    if(a.board[sugx1][sugy1])
                        printCell(0, a.board[sugx1][sugy1] % 6 + 9, a.board[sugx1][sugy1], sugx1, sugy1);
                    
                    else
                        clearCell(0, a, sugx1, sugy1);
            
            if(sugx2 == x1 && sugy2 == y1)
                printCell(6, 14, a.board[sugx2][sugy2], sugx2, sugy2);
            
            else
                if(sugx2 == curX && sugy2 == curY)
                    printCell(8, 7, a.board[sugx2][sugy2], sugx2, sugy2);
                
                else
                    if(a.board[sugx2][sugy2])
                        printCell(0, a.board[sugx2][sugy2] % 6 + 9, a.board[sugx2][sugy2], sugx2, sugy2);
                    
                    else
                        clearCell(0, a, sugx2, sugy2);
            endsugg = false;
        }
		
        if((FcurX != curX) || (FcurY != curY)){
            if(FcurX == x1 && FcurY == y1)
                printCell(6, 14, a.board[FcurX][FcurY], FcurX, FcurY);
            
			else 
				if(((FcurX == sugx1 && FcurY == sugy1) || (FcurX == sugx2 && FcurY == sugy2)) && suggtime)
					printCell(a.board[FcurX][FcurY] % 5 + 1, a.board[FcurX][FcurY] % 6 + 9, a.board[FcurX][FcurY], FcurX, FcurY);
            
				else 
					if(a.board[FcurX][FcurY])
						printCell(0, a.board[FcurX][FcurY] % 6 + 9, a.board[FcurX][FcurY], FcurX, FcurY);
            
					else
						clearCell(0, a, FcurX, FcurY);
            
			if(curX == x1 && curY == y1)
                printCell(6, 14, a.board[curX][curY], curX, curY);
            
			else 
				if(a.board[curX][curY])
					printCell(8, 7, a.board[curX][curY], curX, curY);
            
				else
					clearCell(8, a, curX, curY);
            
			FcurX = curX;
            FcurY = curY;
        }
		
        else{
            if(choose_1){
                printCell(6, 14, a.board[x1][y1], x1, y1);
                choose_1 = false;
            }
            if(hint){
                if(sugx1 != x1 || sugy1 != y1)
                    printCell(a.board[sugx1][sugy1] % 5 + 1, a.board[sugx1][sugy1] % 6 + 9, a.board[sugx1][sugy1], sugx1, sugy1);
                    
                if(sugx2 != x1 || sugy2 != y1)
                    printCell(a.board[sugx2][sugy2] % 5 + 1, a.board[sugx2][sugy2] % 6 + 9, a.board[sugx2][sugy2], sugx2, sugy2);

                hint = false;
            }
            if(choose_2){
                if(a.board[x1][y1])
                    printCell(0, a.board[x1][y1] % 6 + 9, a.board[x1][y1], x1, y1);
                else
                    clearCell(0, a, x1, y1);
                if(a.board[x2][y2])
                    printCell(8, 7, a.board[x2][y2], x2, y2);
                else
                    clearCell(8, a, x2, y2);
                x1 = 0, y1 = 0;
                x2 = 0, y2 = 0;
                choose_2 = false;
            }
        }
    }
}


//////////////////////////////////
// Shuffle the board
void resetBoard(BoardState a){
    int cnt[26];
    for (int i = 0; i < 26; i++)
        cnt[i] = 0;

    for (int i = 1; i <= a.row; i++){
        for (int j = 1; j <= a.col; j++){
            if(a.board[i][j] != 0){
                cnt[a.board[i][j] - (int) 'A'] ++;
                a.board[i][j] = -1;
            }
        }
    }

    for (int i = 1; i <= a.row; i++){
        for (int j = 1; j <= a.col; j++){
            if (a.board[i][j] == -1)
                while (true){
                    char gen = (char) (rand() % 25 + (int)'A');
                    if (cnt[(int) (gen - 'A')] > 0){
                        a.board[i][j] = (int) gen;
                        cnt[(int) (gen - 'A')]--;
                        break;
                    }
                }
        }
    }
}


/////////////////////////////////
// Delete the memory used for the display array
void deleteArt(BoardState &a){
    for (int i = 0; i < 3 * (a.row + 2); i++)
        delete[] a.display[i];
    delete[] a.display;
}


//////////////////////////////////
// Generate art for the background
void generateArt(BoardState &a){
    a.display = new char*[3 * (a.row + 2)];
    for (int i = 0; i < 3 * (a.row + 2); i++)
        a.display[i] = new char[5 * (a.col + 2)];

    ifstream ifs;
	if (a.row <= 6 && a.col <= 6)
		ifs.open("others\\art_1.txt");
    else if (a.row <= 8 && a.col <= 8)
		ifs.open("others\\art_2.txt");
	else 
		ifs.open("others\\art_3.txt");
    if(!ifs.is_open()){
        for (int i = 0; i < 3 * (a.row + 2); i++){
            for (int j = 0; j < 5 * (a.col + 2); j++){
                a.display[i][j] = '.';
            }
        }
    }
    else{
        for (int i = 0; i < 3 * (a.row + 2); i++){
            string str;
            getline(ifs, str, '\n');
            for (int j = 0; j < 5 * (a.col + 2); j++){
                a.display[i][j] = str[j];
            }
        }
    }
    ifs.close();
}


/////////////////////////////
// Drawing matching line
void drawLine(int line[][2])
{
    SetColor(0, 2);
    for (int k = 0; k < 3; k++){
        if(line[k+1][0] == 0 && line[k+1][1] == 0)
            break;
        int x1 = line[k][0], x2 = line[k+1][0], y1 = line[k][1], y2 = line[k+1][1];
        if (x1 == x2){
            if (y1 > y2)
                swap (y1, y2);
            for (int i = y1 * 5 + 4; i <= y2 * 5 + 4; i++){
                    gotoxy(x1 * 3 + 3, i);
                    cout << '*';
                }
        }
        else{
            if (x1 > x2)
                swap (x1, x2);
            for (int i = x1 * 3 + 3; i <= x2 * 3 + 3; i++){
                    gotoxy(i, y1 * 5 + 4);
                    cout << '*';
                }
        }
    }
}


//////////////////////////////////////////////
// Clear the matching line
void clearLine(int line[][2], BoardState a)
{
    SetColor(0, 7);
    for (int k = 0; k < 3; k++){
        if(line[k+1][0] == 0 && line[k+1][1] == 0)
            break;
        int x1 = line[k][0], x2 = line[k+1][0], y1 = line[k][1], y2 = line[k+1][1];
        if (x1 == x2){
            if (y1 > y2)
                swap (y1, y2);
            for (int i = y1 * 5 + 4; i <= y2 * 5 + 4; i++){
                    gotoxy(x1 * 3 + 3, i);
                    cout << a.display[x1 * 3 + 1][i-2];;
                }
        }
        else{
            if (x1 > x2)
                swap (x1, x2);
            for (int i = x1 * 3 + 3; i <= x2 * 3 + 3; i++){
                    gotoxy(i, y1 * 5 + 4);
                    cout << a.display[i-2][y1 * 5 + 2];
                }
        }
    }
}
