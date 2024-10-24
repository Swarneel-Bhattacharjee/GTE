#include "normalmode.h"
#include "mem.h"
#include "kb.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <ncurses/ncurses.h>


int checkCmd(char cmd[MAXCHARBUFLEN]) {
    if (strcmp(cmd, ":q\0") == 0) return QUIT;
    if (strcmp(cmd, ":w\0") == 0) return WRITE;
    if (strcmp(cmd, ":wq\0") == 0) return WRITE_QUIT;
    if (strcmp(cmd, ":nwq\0") == 0) return NOWRITE_QUIT;
    if (strcmp(cmd, ":im\0") == 0) return INPUTMODE;
    
    return -1;
}


void getNormalModeInput(char *key, char cmd[MAXCHARBUFLEN]) {
    int x_ = 0;
    move(terminal_max_y, x_);
    printw("gte>> ");
    x_ = 6;
    move(y, x);

    char c = 0;
    c = getch();

    if (c == ':') {
        move(terminal_max_y, x_);
        clrtoeol();
        int i = 0;
        while (c != K_RET) {
            cmd[i++] = c;
            move(terminal_max_y, x_);
            addch(c);
            x_ ++;
            move(y, x);
            c = getch();
        }

        *key = -1;
        return ;

    } else {
        *key = c; 
    }

    return;    
}


void printToCmdLine(char* str) {
    int x_ = 0;
    move(terminal_max_y, x_);
    clrtoeol();
    printw("gte>> ");
    printw(str);
    move(y, x);
}


void runNormalMode() {
    bool normalModeActive = true;
    char cmd[MAXCHARBUFLEN];
    memset(cmd, 0, sizeof(char)*MAXCHARBUFLEN);
    int i = 0;
    char c = -1;

    while (normalModeActive) {
        memset(cmd, 0, sizeof(char)*MAXCHARBUFLEN);   
        getNormalModeInput(&c, cmd);

        if (c == -1) {
            // since c will remain -1 if cmd is not empty
            switch (checkCmd(cmd)) {
                case QUIT : {
                    if (isDirty) printToCmdLine("Cannot quit, unwritten changes exist");
                    else {
                        isRunning = false;
                        normalModeActive = false;
                        return;
                    } 
                    break;
                }

                case WRITE : {
                    if (isDirty) {
                        writeFile();
                        printToCmdLine("Changes saved");
                    } else printToCmdLine("No changes to write");
                    break;
                }

                case WRITE_QUIT : {
                    if (isDirty) {
                        writeFile();
                        printToCmdLine("Changes saved");
                    }
                    isRunning = false;
                    normalModeActive = false;
                    return;
                    break;
                }

                case NOWRITE_QUIT : {
                    printToCmdLine("Quitting without saving");
                    isRunning = false;
                    normalModeActive = false;
                    return;
                    break;
                }

                case INPUTMODE : {
                    currentMode = STATE_INPUTMODE;
                    normalModeActive = false;
                    break;
                }

                default: {
                    printToCmdLine("Not a valid command");
                    break;
                }
            }

        } else {
            switch (c) {
                case 'h' : 
                case 'j' :
                case 'k' :
                case 'l' :
                case K_UP    : 
                case K_RIGHT : 
                case K_DOWN  : 
                case K_LEFT  : {
                    handleSpclCharPress(c);
                    break;
                }
                 
                default: {
                    break;
                }
            }
        }
    }

    return;
}
