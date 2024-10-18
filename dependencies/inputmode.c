#include "inputmode.h"
#include "mem.h"
#include "scr.h"
#include "kb.h"
#include <ncurses/ncurses.h>


void runInputMode () {
    initscr();
    noecho();
    scrollok(stdscr, TRUE);
    clear(); 

    fillScreen();

    bool inputModeActive = true;
    while (inputModeActive) {
        inputModeActive = handleKeypress();
    }

    currentMode = STATE_NORMALMODE;
    endwin();
}
