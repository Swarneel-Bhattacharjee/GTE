#include "inputmode.h"
#include "mem.h"
#include "scr.h"
#include "kb.h"
#include <ncurses/ncurses.h>


void runInputMode () {
    bool inputModeActive = true;
    while (inputModeActive) {
        inputModeActive = handleKeypress();
    }

    currentMode = STATE_NORMALMODE;
}
