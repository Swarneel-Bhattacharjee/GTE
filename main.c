#include "dependencies/mem.h"
#include "dependencies/scr.h"
#include "dependencies/kb.h"
#include "dependencies/normalmode.h"
#include "dependencies/inputmode.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses/ncurses.h>


void fillspace(int x) {
    for (int i = 0; i < x; i ++) {
        printw(" ");
    }
}

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

    int mid_x = (int)(terminal_max_x * 0.25) - 1;
    int mid_y = (int)(terminal_max_y * 0.5) - 5;
    move(mid_y, mid_x);

    printw("GTE 0.1\n");
    fillspace(mid_x); printw("By Swarneel Bhattacharjee\n");  
    fillspace(mid_x); printw("Command List : -\n");
    fillspace(mid_x); printw("1> :im  :: Go into input mode :: Shows the text in the memory and enables editing\n");
    fillspace(mid_x); printw("2> :q   :: Quit the program   :: If there are no changes to be written to file, then closes the program\n");
    fillspace(mid_x); printw("3> :wq  :: Write then quit    :: Writes any changes to the file and quits the program\n");
    fillspace(mid_x); printw("4> :w   :: Write changes      :: Writes changes to the file\n");
    fillspace(mid_x); printw("5> :nwq :: Quit without write :: Quits program without saving changes if any\n");
    fillspace(mid_x); printw("Press any key to continue\n");
    getch();
    move(0, 0);

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
