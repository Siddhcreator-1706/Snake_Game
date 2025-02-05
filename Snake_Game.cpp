#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <vector>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define getmychar() _getch()
#define kbhit() _kbhit()
#else
#include <stdbool.h>
#include <sys/ioctl.h> // to get terminal size
#include <termios.h>   // setup terminal features
#include <fcntl.h>
#define Sleep usleep

int kbhit()
{
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

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char getmychar()
{
    struct termios oldt, newt;
    char ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
}

#endif

using namespace std;

bool gameRunning = true;
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
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 || w.ws_col == 0) {
        width = 80;  
        height = 25; 
    } else {
        width = w.ws_col;
        height = w.ws_row;
}

#endif
}

class Snake
{
private:
    vector< pair<int, int> > v;
    int length;

public:
    Snake()
    {
        v.push_back({0, 0});
        length = 1;
    }
    int getLength()
    {
        return length;
    }
    void moveSnake() {}
    void changeLength()
    {
        length++;
    }
    void printSnake() {}
};

int setDifficulty()
{
    int difficulty;
    cout << "Enter number to adjust difficulty level: " << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "Difficulty level: ";
    cin >> difficulty;
    switch (difficulty)
    {
    case 3:
        return 100;
        break;
    case 2:
        return 250;
        break;
    case 1:
        return 500;
        break;
    default:
        return 225;
        break;
    }
}

void setColor(int color)
{
    cout << "\033[" << color << "m";
}

void resetColor()
{
    cout << "\033[0m";
}

void printBoard()
{
    int width, height;
    getTerminalSize(width, height);
    width = 3 * min(height, width) / 4;
    height = width;
    setColor(33);
    for (int j = 0; j < height; j++)
    {
        cout << setw(2) << "*";
        for (int i = 0; i < width - 2; i++)
        {
            if (j == 0 || j == height - 1)
                cout << setw(2) << "*";
            else
                cout << setw(2) << " ";
        }
        cout << setw(2) << "*" << endl;
    }
    resetColor();
}

void userInput()
{
    if (kbhit())
    {
        switch (tolower(getmychar()))
        {
        case 'w':
            // Move up
            break;
        case 's':
            // Move down
            break;
        case 'a':
            // Move left
            break;
        case 'd':
            // Move right
            break;
        case 'n':
            gameRunning = false;
            break;
        }
    }
}

int main()
{
    int dfc = setDifficulty();
    printBoard();
    // while (gameRunning)
    // {
    //     userInput();
    //     Sleep(dfc);
    // }
    return 0;
}