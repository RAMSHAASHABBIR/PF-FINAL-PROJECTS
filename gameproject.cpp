#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
HANDLE rcolor = GetStdHandle(STD_OUTPUT_HANDLE);
int temp = 0;
string presskey;
int Cointimer = 5;
string printHeader[41][71];
char arrprint[2][5] = {{'^', '&', '&', '^'}, {'(', '&', ' ', '&', ')'}};                   // array to print hero
char arrghost[2][2] = {{'o', 'o'}, {'!', '!'}};                                            // array to print ghost
bool gameRunning = true;                                                                   // this will tell whether the game is running or not
void printGrid();                                                                          // this will print the maze
void gotoxy(int x, int y);                                                                 // this will help to give x and y coordinates to all the characters
void erase(int x, int y);                                                                  // this will help to erase the hero husty
void clear(int x, int y, char previous);                                                   // this will help to erase the ghosts
void showGhost(int x, int y);                                                              // this will help to print the ghost
void printHusty(int x, int y);                                                             // this will help to print the hero
char getCharAtxy(short int x, short int y);                                                // this will help to see the next place of moving character
void generateBullet1(int &, int &, int[4000], int[4000], bool[4000], int &);               // this will help to generate bullet from gun1
void generateBullet2(int &, int &, int coinsX[4000], int coinsY[4000], bool[4000], int &); // this will help to generate bullet from gun3
void generateBullet3(int &, int &, int[4000], int[4000], bool[4000], int &);               // this will help to generate bullet from gun5
void generateBullet4(int &, int &, int coinsX[4000], int coinsY[4000], bool[4000], int &); // this will help to generate coin from gun2
void generateBullet5(int &, int &, int[4000], int[4000], bool[4000], int &);               // this will help to generate coin from gun4
void generateBullet6(int &, int &, int coinsX[4000], int coinsY[4000], bool[4000], int &); // this will help to generate coin from gun6
void moveBullet(int &, int[4000], int[4000], bool[4000], int &);                           // this will help to move bullets from the guns
void moveCoins(int &, int[4000], int[4000], bool[4000], int &);                            // this will help to move coins from the guns
void print(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &);          // this will help to print that how much hero health will decrease
void print1(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &);         // this will help to print how much coins hero have collect
void decreaseHealth(int &);                                                                // this will help to count how many times health has decreased
void coinCollect(int &);                                                                   // this will help to count how much coins hero have collect
void printBullet(int x, int y);                                                            // this will help to print the bullet so that it can move forward
void printCoins(int x, int y);                                                             // this will help to print the coins so that it can move forward
void eraseBullet(int x, int y);                                                            // this will help to erase the bullets
void eraseCoins(int x, int y);                                                             // this will help to erase the coins
void makeBulletInactive(int index, bool[4000]);                                            // this will help to stop bullets generating from gun
void makeCoinsInactive(int index, bool[4000]);                                             // this will help to stop coins generating from gun
void hustyGhostCollision(int &, int &, int &);                                             // this will help to detect hero and ghost collision
void scoreToFile(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &);
void scoreToArray(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &);
void mazeFromFile();

string starter();
main()
{
    int gun1X = 4;
    int gun1Y = 4;
    int gun2X = 13;
    int gun2Y = 4;
    int gun3X = 26;
    int gun3Y = 4;
    int gun4X = 37;
    int gun4Y = 4;
    int gun5X = 52;
    int gun5Y = 4;
    int gun6X = 64;
    int gun6Y = 4;
    int score = 0;
    int score1 = 0;
    int snakyX = 2;
    int snakyY = 22;
    int angryX = 52;
    int angryY = 20;
    int hustyX = 9;
    int hustyY = 9;
    int blackyX = 4;
    int blackyY = 4;
    int bulletCount = 0;
    int coinsCount = 0;
    int bulletX[4000];
    int bulletY[4000];
    int coinsX[4000];
    int coinsY[4000];
    bool isBulletActive[4000];
    bool isCoinsActive[4000];
    string direction = "right";
    string direction2 = "right";
    string direction1 = "down";
    char previouschar = ' ';
    system("cls");
    // we have to select from 1 to 3 options
    string check = starter();
    // if we select option 1 we can play or start a new game
    if (check == "1")
    {
        mazeFromFile();
        gameRunning = true;
        system("cls");
        printGrid();
        printHusty(hustyX, hustyY);
        print(score, score1, hustyX, hustyY, angryX, angryY, blackyX, blackyY, snakyX, snakyY);
    }
    // if we select option 2 we can play our resume game
    else if (check == "2")
    {
        scoreToArray(score, score1, hustyX, hustyY, angryX, angryY, blackyX, blackyY, snakyX, snakyY);
        mazeFromFile();
        gameRunning = true;
        system("cls");
        printGrid();
        printHusty(hustyX, hustyY);
        print(score, score1, hustyX, hustyY, angryX, angryY, blackyX, blackyY, snakyX, snakyY);
    }
    // if we select option 3 we can exit
    else if (check == "3")
    {
        abort();
    }
    // if we select 1 or 2 game running is true then game will start
    while (gameRunning == true)
    {
        hustyGhostCollision(score, hustyX, hustyY);
        print(score, score1, hustyX, hustyY, angryX, angryY, blackyX, blackyY, snakyX, snakyY);
        print1(score, score1, hustyX, hustyY, angryX, angryY, blackyX, blackyY, snakyX, snakyY);
        char nextLocation;
        char nextLocation2;
        char nextLocation3;
        char nextLocation4;
        char nextLocation5;
        char nextLocation6;
        char nextLocation7;
        char nextLocation8;
        char nextLocation9;
        char nextLocation10;
        char nextLocation11;
        // with this hero can move in left position
        if (GetAsyncKeyState(VK_LEFT))
        {
            nextLocation = getCharAtxy(hustyX - 1, hustyY);
            nextLocation2 = getCharAtxy(hustyX - 1, hustyY + 1);
            if (nextLocation == ' ' && nextLocation2 == ' ')
            {
                erase(hustyX, hustyY);
                hustyX = hustyX - 1;
                printHusty(hustyX, hustyY);
            }
        }
        // with this hero can move in right position
        if (GetAsyncKeyState(VK_RIGHT))
        {
            nextLocation = getCharAtxy(hustyX + 4, hustyY);
            nextLocation2 = getCharAtxy(hustyX + 5, hustyY + 1);
            if (nextLocation == ' ' && nextLocation2 == ' ')
            {
                erase(hustyX, hustyY);
                hustyX = hustyX + 1;
                printHusty(hustyX, hustyY);
            }
        }
        // with this hero can move at up position
        if (GetAsyncKeyState(VK_UP))
        {
            nextLocation3 = getCharAtxy(hustyX, hustyY - 1);
            nextLocation4 = getCharAtxy(hustyX + 1, hustyY - 1);
            nextLocation5 = getCharAtxy(hustyX + 2, hustyY - 1);
            nextLocation6 = getCharAtxy(hustyX + 3, hustyY - 1);
            nextLocation7 = getCharAtxy(hustyX + 4, hustyY - 1);

            if (nextLocation3 == ' ' && nextLocation4 == ' ' && nextLocation5 == ' ' && nextLocation6 == ' ' && nextLocation7 == ' ')
            {
                erase(hustyX, hustyY);
                hustyY = hustyY - 1;
                printHusty(hustyX, hustyY);
            }
        }
        // with this hero can move at down position
        if (GetAsyncKeyState(VK_DOWN))
        {
            nextLocation3 = getCharAtxy(hustyX, hustyY + 2);
            nextLocation4 = getCharAtxy(hustyX + 1, hustyY + 2);
            nextLocation5 = getCharAtxy(hustyX + 2, hustyY + 2);
            nextLocation6 = getCharAtxy(hustyX + 3, hustyY + 2);
            nextLocation7 = getCharAtxy(hustyX + 4, hustyY + 2);

            if (nextLocation3 == ' ' && nextLocation4 == ' ' && nextLocation5 == ' ' && nextLocation6 == ' ' && nextLocation7 == ' ')
            {
                erase(hustyX, hustyY);
                hustyY = hustyY + 1;
                printHusty(hustyX, hustyY);
            }
        }
        // if we click escape game will stop
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false;
        }
        Sleep(200);
        // snaky will continuously wander right and left
        if (direction == "right")
        {
            nextLocation8 = getCharAtxy(snakyX + 2, snakyY);
            nextLocation9 = getCharAtxy(snakyX + 2, snakyY + 1);
            if (nextLocation8 == '#' && nextLocation9 == '#')
            {
                clear(snakyX, snakyY, previouschar);
                direction = "left";
            }
            if (nextLocation8 == ' ' && nextLocation9 == ' ')
            {
                clear(snakyX, snakyY, previouschar);
                snakyX = snakyX + 1;
                showGhost(snakyX, snakyY);
            }
        }
        // snaky can move left with help of this
        if (direction == "left")
        {
            nextLocation8 = getCharAtxy(snakyX - 1, snakyY);
            nextLocation9 = getCharAtxy(snakyX - 1, snakyY + 1);
            if (nextLocation8 == '#' && nextLocation9 == '#')
            {
                direction = "right";
            }
            if (nextLocation8 == ' ' && nextLocation9 == ' ')
            {
                clear(snakyX, snakyY, previouschar);
                snakyX = snakyX - 1;
                showGhost(snakyX, snakyY);
            }
        }
        // angry can continously wander up and down
        if (direction1 == "down")
        {
            nextLocation8 = getCharAtxy(angryX, angryY + 2);
            nextLocation9 = getCharAtxy(angryX + 1, angryY + 2);

            if (nextLocation8 == '*' || nextLocation9 == '*')
            {
                direction1 = "up";
            }
            else if (nextLocation8 == ' ' && nextLocation9 == ' ')
            {
                clear(angryX, angryY, previouschar);
                angryY = angryY + 1;
                showGhost(angryX, angryY);
            }
        }
        // angry can move up with help of this
        if (direction1 == "up")
        {
            nextLocation8 = getCharAtxy(angryX, angryY - 1);
            nextLocation9 = getCharAtxy(angryX + 1, angryY - 1);
            if (nextLocation8 == '*' && nextLocation9 == '*')
            {
                direction1 = "down";
            }
            else if (nextLocation8 == ' ' && nextLocation9 == ' ')
            {
                clear(angryX, angryY, previouschar);
                angryY = angryY - 1;
                showGhost(angryX, angryY);
            }
        }
        // balcky is the chasing ghost which is chasing hero according to following condition
        if (blackyX < hustyX)
        {
            nextLocation10 = getCharAtxy(blackyX + 2, blackyY);
            nextLocation11 = getCharAtxy(blackyX + 2, blackyY + 1);
            if (nextLocation10 == ' ' && nextLocation11 == ' ')
            {
                clear(blackyX, blackyY, ' ');
                blackyX = blackyX + 1;
                showGhost(blackyX, blackyY);
            }
        }
        else if (blackyX > hustyX)
        {
            nextLocation10 = getCharAtxy(blackyX - 1, blackyY);
            nextLocation11 = getCharAtxy(blackyX - 1, blackyY + 1);
            if (nextLocation10 == ' ' && nextLocation11 == ' ')
            {
                clear(blackyX, blackyY, ' ');
                blackyX = blackyX - 1;
                showGhost(blackyX, blackyY);
            }
        }
        else if (blackyY > hustyY)
        {
            nextLocation10 = getCharAtxy(blackyX, blackyY - 1);
            nextLocation11 = getCharAtxy(blackyX + 1, blackyY - 1);
            if (nextLocation10 == ' ' && nextLocation11 == ' ')
            {
                clear(blackyX, blackyY, ' ');
                blackyY = blackyY - 1;
                showGhost(blackyX, blackyY);
            }
            else if (nextLocation10 == '*' || nextLocation11 == '*')
            {
                clear(blackyX, blackyY, previouschar);
                blackyY = blackyY + 0;
                showGhost(blackyX, blackyY);
            }
        }
        else if (blackyY < hustyY)
        {
            nextLocation10 = getCharAtxy(blackyX, blackyY + 2);
            nextLocation11 = getCharAtxy(blackyX + 1, blackyY + 2);
            if (nextLocation10 == ' ' && nextLocation11 == ' ')
            {
                clear(blackyX, blackyY, ' ');
                blackyY = blackyY + 1;
                showGhost(blackyX, blackyY);
            }
            else if (nextLocation10 == '*' || nextLocation11 == '*')
            {
                clear(blackyX, blackyY, previouschar);
                blackyY = blackyY + 0;
                showGhost(blackyX, blackyY);
            }
        }
        // this will help for continously falling of bullets and coins
        if (Cointimer <= 0)
        {
            Cointimer = 15;
            generateBullet1(gun1X, gun1Y, bulletX, bulletY, isBulletActive, bulletCount);
            generateBullet2(gun2X, gun2Y, coinsX, coinsY, isCoinsActive, coinsCount);
            generateBullet3(gun3X, gun3Y, bulletX, bulletY, isBulletActive, bulletCount);
            generateBullet4(gun4X, gun4Y, coinsX, coinsY, isCoinsActive, coinsCount);
            generateBullet5(gun5X, gun5Y, bulletX, bulletY, isBulletActive, bulletCount);
            generateBullet6(gun6X, gun6Y, coinsX, coinsY, isCoinsActive, coinsCount);
        }
        else
        {
            Cointimer--;
        }
        moveCoins(score1, coinsX, coinsY, isCoinsActive, coinsCount);
        moveBullet(score, bulletX, bulletY, isBulletActive, bulletCount);
    }
}
// this will print user menu
string starter()
{
    cout << "************************************************************************************" << endl;
    cout << "************************************************************************************" << endl;
    cout << "********************************SURVIVAL OF HUSTY***********************************" << endl;
    cout << "************************************************************************************" << endl;
    cout << "************************************************************************************" << endl;
    cout << "                                                                                    " << endl;
    cout << "1.New game" << endl;
    cout << "2.Resume game" << endl;
    cout << "3.Exit" << endl;
    getline(cin, presskey);
    return presskey;
}
// this will help to print the maze
void printGrid()
{

    SetConsoleTextAttribute(rcolor,4);
    for (int j = 0; j < 41; j++)
    {
        cout << endl;
        for (int m = 0; m < 71; m++)
        {
            cout << printHeader[j][m];
        }
    }
}
// this will help to set the coordinates x and y 
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
// this will help to print husty
void printHusty(int x, int y)
{
    SetConsoleTextAttribute(rcolor,1);
    for (int j = 0; j < 2; j++)
    {
        gotoxy(x, y + j);
        for (int m = 0; m < 5; m++)
        {
            cout << arrprint[j][m];
        }
    }
}
// this will help to erase hero husty
void erase(int x, int y)
{
    gotoxy(x, y);
    cout << "    ";
    gotoxy(x, y + 1);
    cout << "     ";
}
// this will help to see next place of moving characters
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
// this will help to erase the ghost
void clear(int x, int y, char previous)
{
    gotoxy(x, y);
    cout << "  ";
    gotoxy(x, y + 1);
    cout << "  ";                
}
// this will help to print the ghost
void showGhost(int x, int y)
{
    SetConsoleTextAttribute(rcolor,6);
    for (int j = 0; j < 2; j++)
    {
        gotoxy(x, y + j);
        for (int m = 0; m < 2; m++)
        {
            cout << arrghost[j][m];
        }
    }
}
// this will help to generate bullet from gun1
void generateBullet1(int &gun1X, int &gun1Y, int bulletX[4000], int bulletY[4000], bool isBulletActive[4000], int &bulletCount)
{
    bulletX[bulletCount] = gun1X;
    bulletY[bulletCount] = gun1Y;
    isBulletActive[bulletCount] = true;
    gotoxy(bulletX[bulletCount], bulletY[bulletCount]);
    cout << ".";
    bulletCount++;
}
// this will help to generate bullet from gun3
void generateBullet3(int &gun3X, int &gun3Y, int bulletX[4000], int bulletY[4000], bool isBulletActive[4000], int &bulletCount)
{
    bulletX[bulletCount] = gun3X;
    bulletY[bulletCount] = gun3Y;
    isBulletActive[bulletCount] = true;
    gotoxy(bulletX[bulletCount], bulletY[bulletCount]);
    cout << ".";
    bulletCount++;
}
// this will help to generate bullet from gun5
void generateBullet5(int &gun5X, int &gun5Y, int bulletX[4000], int bulletY[4000], bool isBulletActive[4000], int &bulletCount)
{
    bulletX[bulletCount] = gun5X;
    bulletY[bulletCount] = gun5Y;
    isBulletActive[bulletCount] = true;
    gotoxy(bulletX[bulletCount], bulletY[bulletCount]);
    cout << ".";
    bulletCount++;
}
// this will help to generate coins from gun2
void generateBullet2(int &gun2X, int &gun2Y, int coinsX[4000], int coinsY[4000], bool isCoinsActive[4000], int &coinsCount)
{
    coinsX[coinsCount] = gun2X;
    coinsY[coinsCount] = gun2Y;
    isCoinsActive[coinsCount] = true;
    gotoxy(coinsX[coinsCount], coinsY[coinsCount]);
    cout << "$";
    coinsCount++;
}
// this will help to generate coins from gun4
void generateBullet4(int &gun4X, int &gun4Y, int coinsX[4000], int coinsY[4000], bool isCoinsActive[4000], int &coinsCount)
{
    coinsX[coinsCount] = gun4X;
    coinsY[coinsCount] = gun4Y;
    isCoinsActive[coinsCount] = true;
    gotoxy(coinsX[coinsCount], coinsY[coinsCount]);
    cout << "$";
    coinsCount++;
}
// this will help to generate coins from gun6
void generateBullet6(int &gun6X, int &gun6Y, int coinsX[4000], int coinsY[4000], bool isCoinsActive[4000], int &coinsCount)
{
    coinsX[coinsCount] = gun6X;
    coinsY[coinsCount] = gun6Y;
    isCoinsActive[coinsCount] = true;
    gotoxy(coinsX[coinsCount], coinsY[coinsCount]);
    cout << "$";
    coinsCount++;
}
// this will help to make bullet inactive
void makeBulletInactive(int index, bool isBulletActive[4000])
{
    isBulletActive[index] = false;
}
// this will help to make coins inactive
void makeCoinsInactive(int index, bool isCoinsActive[4000])
{
    isCoinsActive[index] = false;
}
// this will help to print the bullet
void printBullet(int x, int y)
{
   SetConsoleTextAttribute(rcolor,6);
    gotoxy(x, y);
    cout << ".";
}
// this will help to print the coins
void printCoins(int x, int y)
{
    SetConsoleTextAttribute(rcolor,1);
    gotoxy(x, y);
    cout << "$";
}
// this will help to erase the bullet
void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
// this will help to erase the coins
void eraseCoins(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
// this will help to move the bullet in maze
void moveBullet(int &score, int bulletX[4000], int bulletY[4000], bool isBulletActive[4000], int &bulletCount)
{
    for (int y = 0; y < bulletCount; y++)
    {
        if (isBulletActive[y] == true)
        {
            char next = getCharAtxy(bulletX[y], bulletY[y] + 1);
            if (next == ' ')
            {
                eraseBullet(bulletX[y], bulletY[y]);
                bulletY[y] = bulletY[y] + 1;
                printBullet(bulletX[y], bulletY[y]);
            }
            else if (next == '*')
            {
                eraseBullet(bulletX[y], bulletY[y]);
                next = getCharAtxy(bulletX[y], bulletY[y] + 2);
                if (next == ' ')
                {
                    eraseBullet(bulletX[y], bulletY[y]);
                    bulletY[y] = bulletY[y] + 2;
                    printBullet(bulletX[y], bulletY[y]);
                }
                // this will help to detect the husty and bullet collision
                else if (next == '^' || next == '&' || next == ')')
                {
                    decreaseHealth(score);
                    eraseBullet(bulletX[y], bulletY[y]);
                    makeBulletInactive(y, isBulletActive);
                }
            }
            else if (next == '^' || next == '&' || next == ')')
            {

                decreaseHealth(score);
                eraseBullet(bulletX[y], bulletY[y]);
                makeBulletInactive(y, isBulletActive);
            }
            else
            {
                eraseBullet(bulletX[y], bulletY[y]);
                makeBulletInactive(y, isBulletActive);
            }
        }
    }
}
void moveCoins(int &score1, int coinsX[4000], int coinsY[4000], bool isCoinsActive[4000], int &coinsCount)
{
    for (int y = 0; y < coinsCount; y++)
    {
        if (isCoinsActive[y] == true)
        {

            char next = getCharAtxy(coinsX[y], coinsY[y] + 1);
            if (next == ' ')
            {
                eraseCoins(coinsX[y], coinsY[y]);
                coinsY[y] = coinsY[y] + 1;
                printCoins(coinsX[y], coinsY[y]);
            }
            else if (next == '*')
            {
                eraseCoins(coinsX[y], coinsY[y]);
                next = getCharAtxy(coinsX[y], coinsY[y] + 2);
                if (next == ' ')
                {
                    eraseCoins(coinsX[y], coinsY[y]);
                    coinsY[y] = coinsY[y] + 2;
                    printCoins(coinsX[y], coinsY[y]);
                }
                // this will help to detect the husty and coins collision
                else if (next == '^' || next == '&' || next == ')')
                {
                    coinCollect(score1);
                    eraseCoins(coinsX[y], coinsY[y]);
                    makeCoinsInactive(y, isCoinsActive);
                }
            }
            else if (next == '^' || next == '&' || next == ')')
            {
                coinCollect(score1);
                eraseCoins(coinsX[y], coinsY[y]);
                makeCoinsInactive(y, isCoinsActive);
            }
            else
            {
                eraseCoins(coinsX[y], coinsY[y]);
                makeCoinsInactive(y, isCoinsActive);
            }
        }
    }
}
// this will help to decrease hero health when ghost or bullet touch him
void decreaseHealth(int &score)
{
    score++;
}
// this will help to print the decreasing health of hero
void print(int &score, int &score1, int &hustyX, int &hustyY, int &angryX, int &angryY, int &blackyX, int &blackyY, int &snakyX, int &snakyY)
{
    gotoxy(90, 10);
    cout << "Decreasing health"
         << "=" << score << "/11";
    scoreToFile(score, score1, hustyX, hustyY, angryX, angryY, blackyX, blackyY, snakyX, snakyY);
    if (score > 10)
    {
        system("cls");
        cout << "************************************************************************************" << endl;
        cout << "************************************************************************************" << endl;
        cout << "****************************************GAME OVER***********************************" << endl;
        cout << "****************************************YOU LOSE************************************" << endl;
        cout << "************************************************************************************" << endl;
        cout << "                                                                                    " << endl;
        cout << "Your score is " << score1 << endl;
        abort();
    }
}
// this will help to count the collected coins by husty
void coinCollect(int &score1)
{
    score1++;
}
// this will help to print the score made by husty
void print1(int &score, int &score1, int &hustyX, int &hustyY, int &angryX, int &angryY, int &blackyX, int &blackyY, int &snakyX, int &snakyY)
{
    gotoxy(90, 20);
    cout << " Your score"
         << "=" << score1 << "/11";
    scoreToFile(score, score1, hustyX, hustyY, angryX, angryY, blackyX, blackyY, snakyX, snakyY);
    if (score1 > 10)
    {
        system("cls");
        cout << "************************************************************************************" << endl;
        cout << "************************************************************************************" << endl;
        cout << "****************************************GAME END************************************" << endl;
        cout << "****************************************YOU WON*************************************" << endl;
        cout << "************************************************************************************" << endl;
        cout << "                                                                                    " << endl;
        cout << "Your score is " << score1 << endl;
        abort();
    }
}
// this will help to detect ghost and hero collision
void hustyGhostCollision(int &score, int &hustyX, int &hustyY)
{
    char nextLocation[12];

    nextLocation[0] = getCharAtxy(hustyX + 4, hustyY);
    nextLocation[1] = getCharAtxy(hustyX + 5, hustyY + 1);

    nextLocation[2] = getCharAtxy(hustyX, hustyY + 2);
    nextLocation[3] = getCharAtxy(hustyX + 1, hustyY + 2);
    nextLocation[4] = getCharAtxy(hustyX + 2, hustyY + 2);
    nextLocation[5] = getCharAtxy(hustyX + 3, hustyY + 2);

    nextLocation[6] = getCharAtxy(hustyX - 1, hustyY);
    nextLocation[7] = getCharAtxy(hustyX - 1, hustyY + 1);

    nextLocation[8] = getCharAtxy(hustyX, hustyY - 1);
    nextLocation[9] = getCharAtxy(hustyX + 1, hustyY - 1);
    nextLocation[10] = getCharAtxy(hustyX + 2, hustyY - 1);
    nextLocation[11] = getCharAtxy(hustyX + 3, hustyY - 1);
    for (int j = 0; j < 12; j++)
    {
        if (nextLocation[j] == 'o' || nextLocation[j] == '!')
        {
            decreaseHealth(score);
            erase(hustyX, hustyY);
            hustyX = 5;
            hustyY = 5;
            printHusty(hustyX, hustyY);
            break;
        }
    }
}
// this will help to store the score,hero and bullet position in the file
void scoreToFile(int &score, int &score1, int &hustyX, int &hustyY, int &snakyX, int &snakyY, int &angryX, int &angryY, int &blackyX, int &blackyY)
{
    fstream file;
    file.open("store.txt", ios::out);
    if (score > 0 || score1 > 0)
    {
        file << score << endl;
        file << score1 << endl;
        file << hustyX << endl;
        file << hustyY << endl;
        file << snakyX << endl;
        file << snakyY << endl;
        file << angryX << endl;
        file << angryY << endl;
        file << blackyX << endl;
        file << blackyY << endl;
        file.close();
        if (score == 11 || score1 == 11)
        {
            file.open("store.txt", ios::out);
            file << 0 << endl;
            file << 0 << endl;
            file << 9 << endl;
            file << 9 << endl;
            file << 2 << endl;
            file << 22 << endl;
            file << 52 << endl;
            file << 20 << endl;
            file << 4 << endl;
            file << 4 << endl;
        }
    }
    else if (score == 0 && score1 == 0)
    {
        score = 0;
        score1 = 0;
        file << score << endl;
        file << score1 << endl;
        file << 9 << endl;
        file << 9 << endl;
        file << 2 << endl;
        file << 22 << endl;
        file << 52 << endl;
        file << 20 << endl;
        file << 4 << endl;
        file << 4 << endl;
    }
    file.close();
}
// this will help to send all the scores and positions to there respective variables
void scoreToArray(int &score, int &score1, int &hustyX, int &hustyY, int &snakyX, int &snakyY, int &angryX, int &angryY, int &blackyX, int &blackyY)
{
    int collect = 0;
    int collect1 = 0;
    int collect2 = 0;
    int collect3 = 0;
    int collect4 = 0;
    int collect5 = 0;
    int collect6 = 0;
    int collect7 = 0;
    int collect8 = 0;
    int collect9 = 0;
    fstream file;
    file.open("store.txt", ios::in);
    file >> collect;
    file >> collect1;
    file >> collect2;
    file >> collect3;
    file >> collect4;
    file >> collect5;
    file >> collect6;
    file >> collect7;
    file >> collect8;
    file >> collect9;
    score = collect;
    score1 = collect1;
    hustyX = collect2;
    hustyY = collect3;
    snakyX = collect4;
    snakyY = collect5;
    angryX = collect6;
    angryY = collect7;
    blackyX = collect8;
    blackyY = collect9;

    file.close();
}
// this will help to bring maze from file and then printing it on screen
void mazeFromFile()
{
    string line;
    fstream file;
    file.open("store1.txt", ios::in);
    int i = 0;
    while (!file.eof())
    {
        getline(file, line);
        for (int j = 0; j < 71; j++)
        {
            printHeader[i][j] = line[j];
        }
        i++;
    }
    file.close();
    i = 0;
}
