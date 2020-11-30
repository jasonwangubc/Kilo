#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios original_terminal_attributes;

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal_attributes);
}

void enableRawMode(){

    tcgetattr(STDIN_FILENO, &original_terminal_attributes);
    
    // registers a function to be called when main returns or exit() is called
    atexit(disableRawMode);

    struct termios raw_terminal_attributes = original_terminal_attributes;

    // ECHO and ICANON are bitflags, bitwise NOT plus AND sets these flags to 0 in c_lflag
    raw_terminal_attributes.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_terminal_attributes);
}

int main(){
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
