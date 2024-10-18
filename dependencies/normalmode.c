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

    char c = 0;
    c = getch();

    if (c == ':') {
        int i = 0;
        while (c != K_RET) {
            c = getch();
            cmd[i++] = c;
            move(terminal_max_y, x_);
            addch(c);
            x_ ++;
            move(y, x);
        }

        *key = 0;
        return ;

    } else {
        *key = c; 
    }

    return;    
}


void runNormalMode() {
    bool normalModeActive = true;
    char cmd[MAXCHARBUFLEN];
    int i = 0;
    memset(cmd, 0, sizeof(char)*MAXCHARBUFLEN);
    char c = -1;

    while (normalModeActive) {
        getNormalModeInput(&c, cmd);

        if (c == 0) {
            // since c will remain 0 if cmd is not empty
            switch (checkCmd(cmd)) {
                case QUIT : {
                    if (isDirty) printf("Cannot quit, unwritten changes exist\n");
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
                        printf("Changes saved\n");
                    } else printf("No changes to write\n");
                    break;
                }

                case WRITE_QUIT : {
                    if (isDirty) {
                        writeFile();
                        printf("Changes saved\n");
                    }
                    isRunning = false;
                    normalModeActive = false;
                    return;
                    break;
                }

                case NOWRITE_QUIT : {
                    printf("Quitting without saving\n");
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
                    printf("Not a valid command %s\n", cmd);
                    break;
                }
            }

        } else {
            c = toupper(c);
            switch (c) {
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
