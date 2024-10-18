#include "dependencies/mem.h"
#include "dependencies/scr.h"
#include "dependencies/kb.h"
#include "dependencies/normalmode.h"
#include "dependencies/inputmode.h"
#include <stdbool.h>
#include <ncurses/ncurses.h>
#include <stdio.h>


int main(int argc, char** argv) {
    
    filename = argv[1];

    loadFile();

    isRunning = true; 
    while (isRunning) {
        if (currentMode == STATE_NORMALMODE) runNormalMode();
        if (currentMode == STATE_INPUTMODE) runInputMode();
    }

    clearMem();
    return 0;
}
