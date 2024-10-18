#include "normalmode.h"
#include "mem.h"
#include <stdbool.h>
#include <string.h>
#include <ncurses/ncurses.h>


int checkCmd(char cmd[MAXCHARBUFLEN]) {
    if (strcmp(cmd, ":q\0") == 0) return QUIT;
    if (strcmp(cmd, ":w\0") == 0) return WRITE;
    if (strcmp(cmd, ":wq\0") == 0) return WRITE_QUIT;
    if (strcmp(cmd, ":nwq\0") == 0) return NOWRITE_QUIT;
    if (strcmp(cmd, ":im\0") == 0) return INPUTMODE;
    
    return -1;
}


void runNormalMode() {
    bool normalModeActive = true;
    char cmd[MAXCHARBUFLEN];
    int i = 0;
    int n = 0;
    memset(cmd, 0, sizeof(char)*MAXCHARBUFLEN);
    char c;

    while (normalModeActive) {
        scanf("%s", cmd);
        checkCmd(cmd);

        n = checkCmd(cmd);
        {
            switch (n) {
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
                    break;
                }
            }
        }
    }

    return;
}
