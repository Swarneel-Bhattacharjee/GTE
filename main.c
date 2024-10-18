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

    loadFile();

    system("CLS");
    printf("GTE 0.1\n");
    printf("By Swarneel Bhattacharjee\n");
    printf("Command List : -\n");
    printf("1> :im  :: Go into input mode :: Shows the text in the memory and enables editing\n");
    printf("2> :q   :: Quit the program   :: If there are no changes to be written to file, then closes the program\n");
    printf("3> :wq  :: Write then quit    :: Writes any changes to the file and quits the program\n");
    printf("4> :w   :: Write changes      :: Writes changes to the file\n");
    printf("5> :nwq :: Quit without write :: Quits program without saving changes if any\n");

    isRunning = true; 
    while (isRunning) {
        if (currentMode == STATE_NORMALMODE) runNormalMode();
        if (currentMode == STATE_INPUTMODE) runInputMode();
    }

    clearMem();
    return 0;
}
