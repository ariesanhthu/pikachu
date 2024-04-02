#include "account.h"
#include "gui.h"

/*
    MENU LOGIN
*/
void showSubMenu(int option)
{
    // điều kiện: nếu đúng thì text color = 3, ngược lại = 6
    SetColor(0, (option == 1) ? 3 : 6);
    cout << "\t\t\t\t ==================" << endl;
    cout << "\t\t\t\t |      GUEST     |" << endl;
    cout << "\t\t\t\t ==================" << endl
         << endl;
    SetColor(0, (option == 2) ? 3 : 6);
    cout << "\t\t\t\t ==================" << endl;
    cout << "\t\t\t\t |      LOGIN     |" << endl;
    cout << "\t\t\t\t ==================" << endl
         << endl;
    SetColor(0, (option == 3) ? 3 : 6);
    cout << "\t\t\t\t ==================" << endl;
    cout << "\t\t\t\t |     REGISTER   |" << endl;
    cout << "\t\t\t\t ==================" << endl
         << endl;
    SetColor(0, (option == 4) ? 3 : 6);
    cout << "\t\t\t\t ==================" << endl;
    cout << "\t\t\t\t |      BACK      |" << endl;
    cout << "\t\t\t\t ==================" << endl
         << endl;
    SetColor(0, 6);
}

/*
    FORM INPUT
*/
void showFormInput(bool isLoginForm)
{
    SetColor(0, 6);
    gotoxy(15, 30);
    cout << "USERNAME";
    gotoxy(16, 30);
    cout << "##################################";
    gotoxy(17, 30);
    cout << "#                                #";
    gotoxy(18, 30);
    cout << "##################################";
    gotoxy(20, 30);
    cout << "PASSWORD";
    gotoxy(21, 30);
    cout << "##################################";
    gotoxy(22, 30);
    cout << "#                                #";
    gotoxy(23, 30);
    cout << "##################################";

    if (!isLoginForm)
    {
        gotoxy(25, 30);
        cout << "PASSWORD CONFIRM";
        gotoxy(26, 30);
        cout << "##################################";
        gotoxy(27, 30);
        cout << "#                                #";
        gotoxy(28, 30);
        cout << "##################################";
    }
}

void login(PlayerState &player, BoardState &a, int &mCurX, int &menu, int &playerid, bool &succlog, int lvlcap[], time_t &oriTime)
{
    // Login menu
    bool log = true;
    int submenu = 1;

    while (!succlog)
    {
        /* SETUP
         */
        ClearScreen();
        // background color, text color
        SetColor(0, 3);

        // Brand Name
        printLogo();

        if (submenu == 1)
        {
            showSubMenu(mCurX);

            // Updating input from keyboard
            // getch() reads a single character from the standard input
            int c = getch(), ch;
            if (c == 224)
                switch (ch = getch())
                {
                case KEY_UP:
                {
                    if (mCurX > 1)
                        mCurX--;
                    else
                        mCurX = 4;
                    break;
                }
                case KEY_DOWN:
                {
                    if (mCurX < 4)
                        mCurX++;
                    else
                        mCurX = 1;
                    break;
                }
                }
            else if (c == KEY_SPACE || c == KEY_ENTER)
            {
                // fstream fs("data\\t.txt", ios::in);
                // fs.write((char *)mCurX, 4);
                // fs.close();

                // start game without login

                if (mCurX == 1)
                {
                    menu = 2;
                    mCurX = 1;
                    return;
                }
                else
                    // BACK
                    if (mCurX == 4)
                    {
                        // RETURN MAIN MENU
                        menu = 1;
                        mCurX = 1;
                        return;
                    }
                    // REGISTER
                    else if (mCurX == 3)
                    {
                        log = false;
                    }
                mCurX = 1;
                submenu++;
            }
        }

        // Login and register
        else
        {
            /*
                SET UP
            */
            // FOMR INPUT
            showFormInput(log);
            ShowConsoleCursor(true);
            SetColor(0, 6);

            // Input username
            char c;
            int countChar = 0;
            gotoxy(17, 32);
            while (c = _getch())
            {
                /*
                    BACK TO MAIN MENU
                */
                if (c == KEY_ESCAPE)
                {
                    menu = 1;
                    return;
                }
                if (c == KEY_ENTER)
                {
                    player.username[countChar] = '\0';
                    break;
                }

                else if (c == 8 && countChar > 0)
                {
                    countChar = ((countChar - 1) > 0 ? countChar - 1 : 0);
                    gotoxy(17, 32 + countChar);
                    cout << " ";
                    gotoxy(17, 32 + countChar);
                }
                else if (c != 8 && countChar < 20 && countChar >= 0)
                {
                    cout << c;
                    player.username[countChar] = c;
                    countChar++;
                }
            }
            gotoxy(17, 32);
            cout << player.username;
            countChar = 0;

            // Input password
            gotoxy(22, 32);
            while (c = _getch())
            {
                /*
                    BACK TO MAIN MENU
                */
                if (c == KEY_ESCAPE)
                {
                    menu = 1;
                    return;
                }
                if (c == KEY_ENTER)
                {
                    player.password[countChar] = '\0';
                    break;
                }

                else if (c == 8 && countChar > 0)
                {
                    countChar = ((countChar - 1) > 0 ? countChar - 1 : 0);
                    gotoxy(22, 32 + countChar);
                    cout << " ";
                    gotoxy(22, 32 + countChar);
                }
                else if (c != 8 && countChar < 20 && countChar >= 0)
                {
                    cout << "*";
                    player.password[countChar] = c;
                    countChar++;
                }
            }

            // Reinputing password if this is register phase
            bool check = true;
            if (!log)
            {
                countChar = 0;
                gotoxy(27, 32);
                char rePass[32] = "";
                while (c = _getch())
                {
                    /*
                        BACK TO MAIN MENU
                    */
                    if (c == KEY_ESCAPE)
                    {
                        menu = 1;
                        return;
                    }
                    if (c == KEY_ENTER)
                    {
                        rePass[countChar] = '\0';
                        break;
                    }

                    else if (c == 8 && countChar > 0)
                    {
                        countChar = ((countChar - 1) > 0 ? countChar - 1 : 0);
                        gotoxy(22, 32 + countChar);
                        cout << " ";
                        gotoxy(22, 32 + countChar);
                    }
                    else if (c != 8 && countChar < 20 && countChar >= 0)
                    {
                        cout << "*";
                        rePass[countChar] = c;
                        countChar++;
                    }
                }
                if (strcmp(player.password, rePass))
                    check = false;
            }

            SetColor(0, 6);
            ShowConsoleCursor(false);

            // If both section is not blank then
            if (strlen(player.username) && strlen(player.password))
            {
                // Check login if this is login phase
                if (log)
                    checkLogin(player, playerid, succlog, submenu);

                // Check register if this is register phase
                else if (check)
                    checkRegis(player, playerid, succlog, submenu, log);
                else
                {
                    gotoxy(30, 30);
                    cout << "PASSWORDS DO NOT MATCH!";
                    getch();
                }

                /*
                    LOGIN SUCCESSFULLY
                */
                if (succlog)
                {
                    loadGame(player, playerid, a, lvlcap, oriTime);

                    menu = 8;
                    mCurX = 1;
                    return;
                }
            }

            // If both section is blank
            else
            {
                gotoxy((log) ? 25 : 30, 30);
                cout << "INVALID!";
                getch();
                submenu = 1;
                log = true;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////
void checkLogin(PlayerState player, int &playerid, bool &succ, int &submenu)
{
    // Reading file for checking login
    ifstream ifs("data\\account.dat", ios::binary);
    int n = 0;
    ifs.seekg(0, ios::end);
    int len = ifs.tellg();
    ifs.seekg(0, ios::beg);
    while (ifs.tellg() < len)
    {
        char usercheck[32], passcheck[32];
        ifs.read((char *)usercheck, 32);
        ifs.read((char *)passcheck, 32);
        ifs.seekg(608, ios::cur);
        if (!strcmp(usercheck, player.username) && !strcmp(passcheck, player.password))
        {
            succ = true;
            playerid = n;
            break;
        }
        n++;
    }
    if (succ)
    {
        gotoxy(25, 30);
        cout << "LOGIN SUCCESSFULLY";
    }
    else
    {
        gotoxy(25, 30);
        cout << "WRONG USERNAME OR PASSWORD!";
        submenu = 1;
    }
    // getch();
    ifs.close();
}

/////////////////////////////////////////////////////////////////////////////////////////
// Checking if register is valid
void checkRegis(PlayerState &player, int &playerid, bool &succ, int &submenu, bool &log)
{
    // Reading file for checking register
    fstream fs("data\\account.dat", ios::out | ios::in | ios::binary);
    int n = 0;
    bool check = true;
    fs.seekg(0, ios::end);
    int len = fs.tellg();
    fs.seekg(0, ios::beg);
    while (fs.tellg() < len)
    {
        char usercheck[32];
        fs.read((char *)usercheck, 32);
        fs.seekg(640, ios::cur);
        if (!strcmp(usercheck, player.username))
        {
            gotoxy(30, 30);
            cout << "USERNAME EXISTS";
            check = false;
            submenu = 1;
            log = true;
            getch();
            break;
        }
        n++;
    }
    if (check)
    {
        playerid = n;
        player.mode = 0;
        player.lvl = 1;
        player.lvlstate = 1;
        player.count = 24;
        player.timeleft = 220;
        player.score = 0;
        int board[2] = {4, 6};
        fs.seekp(0, ios::end);
        fs.write((char *)&player, sizeof(player));
        fs.write((char *)board, 584);
        succ = true;
        gotoxy(30, 30);
        cout << "REGISTER SUCCESSFULLY";
        getch();
    }
    fs.close();
}

///////////////////////////////////////////////////////////////
// Writing save game
void saveGame(PlayerState player, int playerid, BoardState a)
{
    // Loading save data if successfully login
    fstream fs("data\\account.dat", ios::binary | ios::in | ios::out);
    fs.seekp(playerid * 672, ios::beg);
    fs.write((char *)&player, sizeof(player));
    fs.write((char *)&a.row, 4);
    fs.write((char *)&a.col, 4);
    for (int i = 0; i < a.row + 2; i++)
        fs.write((char *)a.board[i], (a.col + 2) * 4);
    int temp = 0;
    for (int i = 0; i < 144 - (a.row + 2) * (a.col + 2); i++)
        fs.write((char *)&temp, 4);
    fs.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Loading save game
void loadGame(PlayerState &player, int playerid, BoardState &a, int lvlcap[], time_t &oriTime)
{
    // Loading save game for certain accounts
    ifstream ifs("data\\account.dat", ios::binary);
    ifs.seekg(playerid * 672, ios::beg);
    ifs.read((char *)&player, sizeof(player));
    cout << sizeof(player);
    ifs.read((char *)&a.row, 4);
    ifs.read((char *)&a.col, 4);
    if (player.mode)
    {
        a.board = new int *[a.row + 2];
        for (int i = 0; i < a.row + 2; i++)
            a.board[i] = new int[a.col + 2];
        for (int i = 0; i < a.row + 2; i++)
            ifs.read((char *)a.board[i], (a.col + 2) * 4);
    }
    int temp = player.lvl;
    while (temp - (9 - lvlcap[8]) > 0)
    {
        temp -= (9 - lvlcap[8]);
        for (int i = 8; i >= 1; i--)
        {
            if (lvlcap[i] != i)
            {
                lvlcap[i]++;
                for (int u = i + 1; u < 9; u++)
                    lvlcap[u] = lvlcap[u - 1] + 1;
                break;
            }
        }
    }
    lvlcap[9] = temp + lvlcap[8];
    oriTime = time(0) - (220 - player.timeleft);
    ifs.close();
}

/////////////////////////////////
// Loading leaderboard
void loadLB(LeaderBoard &lb)
{
    fstream fs("data\\lb.dat", ios::in | ios::out | ios::binary);
    fs.read((char *)&lb, sizeof(lb));
    fs.close();
}

///////////////////////////////////////////////////
// Updating leaderboard
void updateLB(LeaderBoard &lb, PlayerState player)
{
    // if(player.username == "") return;
    switch (player.mode)
    {
    // Easy mode
    case 1:
    {
        for (int i = 0; i < 5; i++)
            if (lb.hsEasy[i] < player.score)
            {
                for (int u = 4; u > i; u--)
                {
                    lb.hsEasy[u] = lb.hsEasy[u - 1];
                    strcpy(lb.userEasy[u], lb.userEasy[u - 1]);
                }
                lb.hsEasy[i] = player.score;
                strcpy(lb.userEasy[i], player.username);
                break;
            }
        break;
    }

    // Medium mode
    case 2:
    {
        for (int i = 0; i < 5; i++)
            if (lb.hsMedium[i] < player.score)
            {
                for (int u = 4; u > i; u--)
                {
                    lb.hsMedium[u] = lb.hsMedium[u - 1];
                    strcpy(lb.userMedium[u], lb.userMedium[u - 1]);
                }
                lb.hsMedium[i] = player.score;
                strcpy(lb.userMedium[i], player.username);
                break;
            }
        break;
    }

    // Hard mode
    case 3:
    {
        for (int i = 0; i < 5; i++)
            if (lb.hsHard[i] < player.score)
            {
                for (int u = 4; u > i; u--)
                {
                    lb.hsHard[u] = lb.hsHard[u - 1];
                    strcpy(lb.userHard[u], lb.userHard[u - 1]);
                }
                lb.hsHard[i] = player.score;
                strcpy(lb.userHard[i], player.username);
                break;
            }
        break;
    }
    }
    ofstream ofs("data\\lb.dat", ios::binary);
    ofs.write((char *)&lb, sizeof(lb));
    ofs.close();
}
