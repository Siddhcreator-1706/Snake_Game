#include <stdio.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define getmychar() _getch()
#define kbhit() _kbhit() 
#else
#include <stdbool.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>

int kbhit() {
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

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char getmychar(){
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

int main() {

    char ch;
    printf("Press any key to continue...\n");
    while (!kbhit()) {
        // Do something while waiting for key press
        printf("HI...");
        ch=getmychar();
        if(getmychar()=='W'){
            while(!kbhit()){
                printf("seed...");
            }
        }
    }
    
    printf("Key Pressed!\n");
    return 0;
}