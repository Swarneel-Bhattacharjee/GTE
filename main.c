#include "dependencies/mem.h"
#include "dependencies/scr.h"
#include "dependencies/kb.h"
#include "dependencies/normalmode.h"
#include "dependencies/inputmode.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses/ncurses.h>


int main(int argc, char** argv) {
    filename = argv[1];

    initscr();
    scrollok(stdscr, TRUE);
    clear(); 

    getmaxyx(stdscr, terminal_max_y, terminal_max_x);
    if (terminal_max_x == -1) {
        printf("Fatal error :: couldnt get terminal dimensions\n");
        exit(1);
    }
    // We need to remove 1 from these values because they give dimensions not indices
    terminal_max_x --;
    terminal_max_y --;

    printw("GTE 0.1\n");
    printw("By Swarneel Bhattacharjee\n");
    printw("Command List : -\n");
    printw("1> :im  :: Go into input mode :: Shows the text in the memory and enables editing\n");
    printw("2> :q   :: Quit the program   :: If there are no changes to be written to file, then closes the program\n");
    printw("3> :wq  :: Write then quit    :: Writes any changes to the file and quits the program\n");
    printw("4> :w   :: Write changes      :: Writes changes to the file\n");
    printw("5> :nwq :: Quit without write :: Quits program without saving changes if any\n");
    printw("Press any key to continue\n");

    clear();
    noecho();
    loadFile();
    fillScreen();


    isRunning = true; 
    while (isRunning) {
        if (currentMode == STATE_NORMALMODE) runNormalMode();
        if (currentMode == STATE_INPUTMODE) runInputMode();
    }

    clearMem();
    return 0;
}
