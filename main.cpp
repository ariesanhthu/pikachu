#include "gameLogic.cpp"
#include "gui.cpp"
#include "account.cpp"

int main()
{
    /*
        SETUP GAME
    */

    // console setting

    // Resize the console window size
    ResizeWindow(0, 0, 900, 850);
    // hide the console blinking cursor
    ShowConsoleCursor(false);

    // Playing music
    PlaySound(TEXT("others/theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    // For random stuff
    srand(time(0));

    // Initialize board, account and leaderboard
    PlayerState player;
    BoardState board;
    LeaderBoard lb;
    loadLB(lb);

    // For level increasing
    int lvlcap[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    // For storing the former cursor
    int FcurX = 1, FcurY = 1;
    // For storing the current cursor
    int curX = 1, curY = 1;
    // For storing two selected cells
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    // For storing the route if there is a path between two cells
    int line[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    // For hint feature
    int sugx1 = 0, sugx2 = 0, sugy1 = 0, sugy2 = 0;
    bool hint = false, choose_1 = false, choose_2 = false, endsugg = false;
    ;

    // For menu settings
    int menu = 1, mCurX = 1;

    // For time setting
    time_t oriTime, suggtime = 0;
    bool eot = false;

    // For the current player
    int playerid = -1;
    bool succlog = false, cont = false, resetcheck = false, newgame = false, suffle = false;

    /*
        GAME PLAY
    */
    while (true)
    {
        /*  MENU NAME INDEX
            0: quit
            1: main
            2: choose game mode
            3: custom game mode
            4: continue game play (data load)
            5: Game play (new game)
            6: Leaderboard
            7: option play with guest role or account
            8: play new game or continue
        
       // ================================================
        
            MENU OPTION AND FLOW
            1: main
                + START:
                    (if user not login) -> 7: option play with guest role or account
                        + GUEST -> 2
                        + LOGIN
                        + REGISTER
                        + BACK -> 1

                    (if user login) -> 8: play new game or continue
                        + NEW GAME -> 2
                        + CONTINUE -> 4: continue game play | if login
                        + LOGOUT -> 1
                        + BACK -> 1

                        2: choose game mode
                            + EASY
                            + MEDIUM
                            + HARD
                            -> 5
                            + CUSTOM -> 3: custom game mode

                        5: Game play

                + LEADERBOARD -> 6: Leaderboard

                + QUIT -> 0: Quit
        */
        ClearScreen();
        printLogo();
        while ((menu > 0 && menu < 4) || menu == 6 || menu == 8)
        {
            // login
            // while (!succlog)
            //     login(player, board, mCurX, menu, playerid, succlog, lvlcap, oriTime);
            ClearScreen(0, 10, 200, 100);
            generateMenu(lb, player.mode, board.row, board.col, menu, mCurX, succlog, cont, player.lvl);
        }
        // Press quit
        if (menu == 0)
        {
            break;
        }
        /*
            ACCOUNT OPTION
        */
        if (menu == 7)
        {
            // if not login, then login and move to the menu section
            login(player, board, mCurX, menu, playerid, succlog, lvlcap, oriTime);
        }
        //------------Gameplay-----------//

        // If there is a save game, then load it
        // If not, then reset
        else if (menu == 4)
        {
            ClearScreen();
            if (cont)
            {
                loadGame(player, playerid, board, lvlcap, oriTime);
                checkLegalMove(board, sugx1, sugy1, sugx2, sugy2);
                cont = false;
            }

            else
            {
                resetGame(board, player.count, player.lvl, lvlcap, curX, curY, FcurX, FcurY);
                generateBoard(board);
                while (!checkLegalMove(board, sugx1, sugy1, sugx2, sugy2))
                    resetBoard(board);
                oriTime = time(0) - min(player.lvl, 100);
            }
            generateArt(board);

            menu++;
            newgame = true;
            srand(time(0));
            string m1 = "others/music_" + to_string(rand() % 4 + 1) + ".wav";
            PlaySound(TEXT(m1.c_str()), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
        // Gameplay
        while (menu == 5)
        {

            // If there is no action, then continuously updating time and cursor pointer
            while (true)
            {
                gotoxy(5, (board.col + 2) * 5 + 5);

                SetColor(0, 6);

                cout << "Level: " << player.lvl << endl;
                showBoard(board, player.lvl, curX, curY, FcurX, FcurY, x1, y1, x2, y2, suggtime, endsugg, sugx1, sugy1, sugx2, sugy2, newgame, hint, choose_1, choose_2);
                showTime(player.timeleft, oriTime, menu, eot, player.score, suggtime, board, endsugg);

                // If there is a key input event, then run the following function
                if (kbhit())
                    keyboardSelect(board, curX, curY, x1, y1, x2, y2, menu, suggtime, oriTime, hint, choose_1, choose_2, suffle);

                // If player press R to shuffle the board
                if (suffle)
                {
                    resetBoard(board);
                    while (!checkLegalMove(board, sugx1, sugy1, sugx2, sugy2))
                        resetBoard(board);
                    resetcheck = true;
                }

                if (resetcheck)
                {
                    bool **temp;
                    for (int i = 1; i <= board.row; i++)
                        for (int u = 1; u <= board.col; u++)
                            if (board.board[i][u])
                                printCell(0, board.board[i][u] % 5 + 9, board.board[i][u], i, u);
                    printCell(8, 7, board.board[curX][curY], curX, curY);
                    oriTime -= 10;
                    resetcheck = false;
                    suffle = false;
                }

                if (choose_2 || menu == 1)
                    break;
            }

            // Updating the board following the action above
            if (menu == 5)
            {

                // If there is actually a path between two cells
                if (findPath(board, x1, x2, y1, y2, line))
                {
                    suggtime = 0;
                    endsugg = true;
                    board.board[x1][y1] = 0;
                    board.board[x2][y2] = 0;
                    player.count -= 2;

                    drawLine(line);
                    Sleep(300);
                    clearLine(line, board);
                    levelCheck(board, x1, y1, x2, y2, player.lvl, lvlcap);
                    showBoard(board, player.lvl, curX, curY, FcurX, FcurY, x1, y1, x2, y2, suggtime, endsugg, sugx1, sugy1, sugx2, sugy2, newgame, hint, choose_1, choose_2);
                    // If there are still cells on the board
                    if (player.count)

                        // Check if there is any valid move on the board, if not then reset the board
                        while (!checkLegalMove(board, sugx1, sugy1, sugx2, sugy2))
                        {
                            resetBoard(board);
                            resetcheck = true;
                        }

                    // Reset the board
                    if (resetcheck)
                    {
                        bool **temp;
                        for (int i = 1; i <= board.row; i++)
                            for (int u = 1; u <= board.col; u++)
                                if (board.board[i][u])
                                    printCell(0, board.board[i][u] % 5 + 9, board.board[i][u], i, u);

                        oriTime -= 10;
                        resetcheck = false;
                    }
                }
                else {
                    printCell(12, 4, board.board[x1][y1], x1, y1);
                    printCell(12, 4, board.board[x2][y2], x2, y2);
                    Sleep(300);
                    showBoard(board, player.lvl, curX, curY, FcurX, FcurY, x1, y1, x2, y2, suggtime, endsugg, sugx1, sugy1, sugx2, sugy2, newgame, hint, choose_1, choose_2);
                }
                for (int i = 0; i < 4; i++)
                    for (int u = 0; u < 2; u++)
                        line[i][u] = 0;

                // If there are no cells left, then let the player continue playing or not
                if (!player.count)
                {
                    calculateScore(player);
                    gotoxy(1, 0);
                    curX = board.row + 2, curY = board.col + 2;
                    FcurX = curX, FcurY = curY;
                    
                    // WIN GAME
                    ClearScreen();
                    loadingPage();

                    SetColor(0, 6);
                    gotoxy(15, 33);
                    cout << "Victory royale!!!!";
                    gotoxy(16, 33);
                    cout << "Your score: " << player.score << endl;

                    // Player choice
                    gotoxy(17, 33);
                    cout << "Continue ?";
                    gotoxy(18, 33);
                    cout << "ENTER to continue.";
                    gotoxy(19, 33);
                    cout << "ESC to quit.";

                    char input;
                    while (input = _getch())
                    {
                        if (input == KEY_ENTER)
                        {
                            player.lvl++;
                            deleteMem(board);
                            deleteArt(board);
                            menu = 4;
                            break;
                        }

                        // If not then update the score record and leaderboard
                        else if (input == KEY_ESCAPE)
                        {
                            updateLB(lb, player);
                            deleteMem(board);
                            deleteArt(board);
                            eraseGame(player, board, lvlcap);
                            saveGame(player, playerid, board);
                            for (int i = 1; i < 10; i++)
                                lvlcap[i] = 0;

                            menu = 1;

                            // Playing music
                            PlaySound(TEXT("others/theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                            break;
                        }
                    }
                }
            }

            // If the game end due to running out of time
            else
            {
                suggtime = 0;
                if (eot)
                {
                    updateLB(lb, player);
                    eraseGame(player, board, lvlcap);
                    eot = false;
                }

                if (player.mode == 4)
                    eraseGame(player, board, lvlcap);

                saveGame(player, playerid, board);
                deleteMem(board);
                deleteArt(board);

                for (int i = 1; i < 10; i++)
                    lvlcap[i] = 0;

                x1 = 0;
                x2 = 0;
                y1 = 0;
                y2 = 0;

                // Playing music
                PlaySound(TEXT("others/theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            }
        }
    }

    return 0;
}