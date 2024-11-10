#include "inputmode.h"
#include "mem.h"
#include "scr.h"
#include "kb.h"
#include <ncurses/ncurses.h>


void runInputMode () {
    bool inputModeActive = true;

    attron(COLOR_PAIR(1));
    while (inputModeActive) {
        inputModeActive = handleKeypress();
    }

    currentMode = STATE_NORMALMODE;
    attroff(COLOR_PAIR(1));
}
