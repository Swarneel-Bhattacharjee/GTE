#include <stdio.h>
#include "dependencies/mem.h"
#include "dependencies/scr.h"
#include "dependencies/kb.h"
#include <stdbool.h>
#include <ncurses/ncurses.h>

int main(int argc, char** argv) {

    initscr();
    noecho();
    scrollok(stdscr, TRUE);

    filename = argv[1];
    loadFile();

    while (true) {
        handleKeypress();
    }

    endwin();

    return 0;
}