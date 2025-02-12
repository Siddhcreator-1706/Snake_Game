#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <stdbool.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termios.h>
#include <fcntl.h>
struct termios orig_termios;
void Sleep(int a)
{
    usleep(1000 * a);
}
void get()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
}
void set()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
#endif

using namespace std;

#define MOVE_CURSOR(x, y) cout << "\033[" << (x) << ";" << (y) << "H"

enum SnakeDirection
{
    Stop = 0,
    Up,
    Down,
    Left,
    Right
};
bool gameRunning = true;
int width, height;

SnakeDirection userInput(SnakeDirection direction)
{
#ifdef _WIN32
    if (_kbhit())
    {
        switch (tolower(_getch()))
        {
        case 'w':
            if (direction != Down)
                return Up;
            break;
        case 's':
            if (direction != Up)
                return Down;
            break;
        case 'a':
            if (direction != Right)
                return Left;
            break;
        case 'd':
            if (direction != Left)
                return Right;
            break;
        default:
            return direction;
            break;
        }
    }
#else
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        switch (tolower(ch))
        {
        case 'w':
            if (direction != Down)
                return Up;
            break;
        case 's':
            if (direction != Up)
                return Down;
            break;
        case 'a':
            if (direction != Right)
                return Left;
            break;
        case 'd':
            if (direction != Left)
                return Right;
            break;
        default:
            return direction;
            break;
        }
    }

#endif
    return direction;
}

void HideCursor()
{
    cout << "\033[?25l";
    cout.flush();
}

void ShowCursor()
{
    cout << "\033[?25h";
    cout.flush();
}

void getTerminalSize(int &width, int &height)
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else
    {
        width = 80;
        height = 25;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 || w.ws_col == 0)
    {
        width = 80;
        height = 25;
    }
    else
    {
        width = w.ws_col;
        height = w.ws_row;
    }

#endif
}

void setSize()
{
    getTerminalSize(width, height);
    width = 3 * width / 4;
    height = 3 * height / 4;
}

void setColor(int color)
{
    cout << "\033[" << color << "m";
}

void resetchange()
{
    cout << "\033[0m";
}

void setbold()
{
    cout << "\033[1m";
}

struct Node
{
    pair<int, int> position;
    Node *next;
    Node(pair<int, int> pos) : position(pos), next(nullptr) {}
};

class Snake
{
private:
    Node *head, *tail;
    int length, prevX, prevY;
    SnakeDirection direction = Up;
    bool grew = false;

public:
    Snake()
    {
        head = new Node({height / 2, width / 2});
        tail = head;
        prevX = height / 2;
        prevY = width / 2;
        length = 1;
    }
    ~Snake()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        length = 0;
    }
    int getLength()
    {
        return length;
    }
    SnakeDirection getdirection()
    {
        return direction;
    }
    void setdirection(SnakeDirection direction)
    {
        this->direction = direction;
    }
    void updateSnake()
    {
        pair<int, int> oldTailPos = tail->position; // Store tail position before update
        prevX = head->position.first;
        prevY = head->position.second;
        pair<int, int> newHead = head->position;
        switch (direction)
        {
        case Up:
            newHead.first--;
            break;
        case Down:
            newHead.first++;
            break;
        case Left:
            newHead.second--;
            break;
        case Right:
            newHead.second++;
            break;
        }
        Node *newNode = new Node(newHead);
        newNode->next = head;
        head = newNode;
        if (!grew)
        {
            Node *temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            delete tail;
            temp->next = nullptr;
            tail = temp;
        }
        else
        {
            grew = false;
        }
        prevX = oldTailPos.first;
        prevY = oldTailPos.second;
    }
    void printSnake()
    {
        MOVE_CURSOR(prevX, prevY);
        cout << " ";
        MOVE_CURSOR(head->position.first, head->position.second);
        setColor(32);
        setbold();
        cout << "o";
        resetchange();
    }
    void changeLength()
    {
        length++;
        grew = true;
    }
    pair<int, int> getHead()
    {
        return head->position;
    }
    Node *getHeadPoint()
    {
        return head;
    }
    void checkBodyCollision()
    {
        Node *temp = head->next;
        while (temp)
        {
            if (temp->position == head->position)
            {
                gameRunning = false;
                break;
            }
            temp = temp->next;
        }
    }
};

class food
{
private:
    int x, y;

public:
    food()
    {
        srand((unsigned)time(0));
        x = rand() % height;
        srand((unsigned)time(0));
        y = rand() % width;
        if (x == 1 || x == 0)
        {
            x = 2;
        }
        if (y == 1 || y == 0)
        {
            y = 2;
        }
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void setCoordinates()
    {
        srand((unsigned)time(0));
        x = rand() % height;
        srand((unsigned)time(0));
        y = rand() % width;
        if (x == 1 || x == 0)
        {
            x = 2;
        }
        if (y == 1 || y == 0)
        {
            y = 2;
        }
    }
    void printFood()
    {
        setColor(31);
        MOVE_CURSOR(x, y);
        cout << "#";
        resetchange();
    }
};

class Game
{
private:
    int score = 0, highscore = 0;
    int difficulty,level;
    string playerName;

public:
    void GetPlayerName()
    {
        cout << "Enter Your Name : ";
        cin >> playerName;
    }
    void RuleBook()
    {
        cout << "Game Rules:" << endl;
        cout << "1. Controls :" << endl;
        cout << " -> W - Move Up" << endl;
        cout << " -> A - Move Left" << endl;
        cout << " -> S - Move Down" << endl;
        cout << " -> D - Move Right" << endl;
        cout << "2. Score :" << endl;
        cout << " For each food you eat your score will be increased by 10." << endl;
        cout << "3. Game End :" << endl;
        cout << " If the head of snake touches it's own body or the border the game is over." << endl;
    }
    void printBoard()
    {
        cout << "\033[2J\033[H";
        cout.flush();
        HideCursor();
        setSize();
        setColor(33);
        for (int i = 0; i <= height; i++)
        {
            for (int j = 0; j <= width; j++)
            {
                if (i == 0 || i == height || j == 0 || j == width)
                {
                    MOVE_CURSOR(i, j);
                    cout << "*"; // Border
                }
            }
        }
        MOVE_CURSOR(height + 1, 1);
        cout << "SCORE :" << endl;
        cout << "HIGHSCORE :";
        resetchange();
    }
    void setDifficulty()
    {
        cout << endl;
        cout << "Enter number to adjust difficulty level: " << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cout << "4. Expert" << endl;
        cout << "Difficulty level: ";
        cin >> level;
        cout << endl;
        while (level < 1 || level > 4)
        {
            cout << "Please Enter valid level: ";
            cin >> level;
            cout << endl;
        }
        switch (level)
        {
        case 4:
            difficulty = 50;
            break;
        case 3:
            difficulty = 100;
            break;
        case 2:
            difficulty = 150;
            break;
        case 1:
            difficulty = 200;
            break;
        }
    }
    void gameResult()
    {
        Sleep(1000);
        cout << "\033[2J\033[H";
        cout.flush();
        setColor(31);
        setbold();
        cout << setw(45) << "*****  *    *  *****  **** " << endl;
        cout << setw(45) << "*   *  *    *  *      *   *" << endl;
        cout << setw(45) << "*   *   *  *   ***    **** " << endl;
        cout << setw(45) << "*   *   *  *   *      * *  " << endl;
        cout << setw(45) << "*****    **    *****  *  * " << endl;
        resetchange();
        setColor(35);
        cout << setw(35) << "HIGH SCORE : " << highscore << endl;
        cout << setw(22) << playerName << ", you scored : " << score << endl;
        if (score == highscore)
        {
            cout << setw(50) << "Congratulations, You are the high scorer!!!" << endl;
        }
        resetchange();
    }
    void gameplay()
    {
        gameRunning = true;
        score = 0;
        int i = 1;
        Snake s;
        food f;
        s.changeLength();
        s.updateSnake();
        s.changeLength();
        s.updateSnake();
        while (gameRunning)
        {
            s.setdirection(userInput(s.getdirection()));
            s.updateSnake();
            if(s.getLength()%5 == 0 && difficulty > 30){
                difficulty-=5;
            }
            if (s.getHead().first <= 1 || s.getHead().first >= height || s.getHead().second <= 1 || s.getHead().second >= width)
            {
                gameRunning = false;
                continue;
            }
            s.checkBodyCollision();

            if (f.getX() == s.getHead().first && f.getY() == s.getHead().second)
            {
                s.changeLength();
                f.setCoordinates();
                Node *temp = s.getHeadPoint();
                while (temp != NULL)
                {
                    if (f.getX() == temp->position.first && f.getX() == temp->position.first)
                    {
                        f.setCoordinates();
                    }
                    else
                    {
                        temp = temp->next;
                    }
                }
                score += 10;
            }
            setColor(33);
            MOVE_CURSOR(height + 1, 8);
            cout << score;
            if (highscore < score)
            {
                highscore = score;
            }
            MOVE_CURSOR(height + 2, 12);
            cout << highscore;
            resetchange();
            s.printSnake();
            f.printFood();
            Sleep(difficulty);
        }
    }
};

int main()
{
#ifndef _WIN32
    get();
#endif
    bool gameloop = true;
    Game g;
    while (gameloop)
    {
        cout << "\033[2J\033[H";
        cout.flush();
        g.GetPlayerName();
        g.RuleBook();
        g.setDifficulty();
        g.printBoard();
        g.gameplay();
        g.gameResult();
        ShowCursor();
        #ifndef _WIN32
    set();
#endif
        setColor(36);
        char choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        cout << endl;
        while (!(choice == 'y' || choice == 'n'))
        {
            cout << "Please Enter Valid input : ";
            cin >> choice;
            cout << endl;
        }
        if (choice == 'n')
        {
            gameloop = false;
        }
        resetchange();
    }
#ifndef _WIN32
    set();
#endif
    return 0;
}
