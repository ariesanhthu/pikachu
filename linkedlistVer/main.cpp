#include "board.cpp"
#include "logic.cpp"

int main()
{
    srand(time(0));
    int col, row;
    headerList *board;
    cout << "Please input the number of rows and columns (col * row must be divisible by 4): ";
    while (true)
    {
        cin >> row >> col;
        if ((col * row) % 4 == 0) break;
        ClearScreen();
        cout << "Invalid input! Please input again: ";
    }
    int level = 1;
    while (true){
        ClearScreen();
        generateBoard(board, col, row, level);
        showBoard(board, col, row, level);
        int cnt = row * col;
        while (cnt > 0)
        {
            int x1, x2, y1, y2;
            gotoxy(row + 2, 0);
            cout << endl << "Please input the index of the first cell (starting from (1, 1)): ";
            cin >> x1 >> y1;
            cout << endl << "Please input the index of the second cell (starting from (1, 1)): ";
            cin >> x2 >> y2;
            if (min(x1, x2) < 0 || max(x1, x2) > row || min(y1, y2) < 0 || max(y1, y2) > col)
                cout << "Invalid input!";
            else
            {
                switch(level)
                {
                   case 1:
                        if (findPath(board, row, col, x1, x2, y1, y2)){
                            trace(traceH(board, x1)->head, y1)->key = 0;
                            trace(traceH(board, x2)->head, y2)->key = 0;
                            cnt -= 2;
                        }
                       break;
                    case 2:
                        if (findPath(board, row, col, x1, x2, y1, y2)){
                            if (x1 != x2)
                            {
                                headerList * cur1 = traceH(board, x1);
                                headerList * cur2 = traceH(board, x2);
                                deleteNode(y1 , cur1);
                                deleteNode(y2 , cur2);
                            }
                            else
                            {
                                headerList * cur = traceH(board, x1);
                                deleteNode(max(y1, y2), cur);
                                deleteNode(min(y1, y2), cur);
                            }
                            cnt -= 2;
                        }
                        break;
                    case 3:
                        if (findPath(board, row, col, x1, x2, col - y1 + 1, col - y2 + 1)){
                            if(x1 != x2)
                            {
                                headerList * cur1 = traceH(board, x1);
                                headerList * cur2 = traceH(board, x2);
                                deleteNode(col - y1 + 1 , cur1);
                                deleteNode(col - y2 + 1 , cur2);
                            }
                            else
                            {
                                headerList * cur = traceH(board, x1);
                                deleteNode(max(col - y1 + 1 , col - y2 + 1), cur);
                                deleteNode(min(col - y1 + 1 , col - y2 + 1), cur);
                            }
                            cnt -= 2;
                        }
                        break;
                    case 4:
                        if (findPath(board, col, row, y1, y2, x1, x2)){
                            if (y1 != y2)
                            {
                                headerList * cur1 = traceH(board, y1);
                                headerList * cur2 = traceH(board, y2);
                                deleteNode(x1 , cur1);
                                deleteNode(x2 , cur2);
                            }
                            else
                            {
                                headerList * cur = traceH(board, y1);
                                deleteNode(max(x1, x2) , cur);
                                deleteNode(min(x1, x2) , cur);
                            }
                            cnt -= 2;
                        }
                        break;
                    case 5:
                        if (findPath(board, col, row, y1, y2, row - x1 + 1, row - x2 + 1)){
                            if (y1 != y2)
                            {
                                headerList * cur1 = traceH(board, y1);
                                headerList * cur2 = traceH(board, y2);
                                deleteNode(row - x1 + 1 , cur1);
                                deleteNode(row - x2 + 1 , cur2);
                            }
                            else
                            {
                                headerList * cur = traceH(board, y1);
                                deleteNode(max(row - x1 + 1 , row - x2 + 1) , cur);
                                deleteNode(min(row - x1 + 1 , row - x2 + 1) , cur);
                            }
                            cnt -= 2;
                        }
                        break;
                }
            }
            ClearScreen();
            showBoard(board, col, row, level);
            if (!checkLegalMove(board, row, col, level))
                break;
        }
        if (cnt != 0)
        {
            gotoxy(row + 2, 0);
            cout << "LOSER!!!" << endl;
            getch();
        }
        else
            level++;

        if (level > 5)
            break;
    }
    return 0;
}
