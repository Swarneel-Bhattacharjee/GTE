#ifndef NORMALMODE_H
#define NORMALMODE_H

#include <stdbool.h>
#include "mem.h"

enum commandList {
    QUIT,
    WRITE,
    WRITE_QUIT,
    NOWRITE_QUIT,
    INPUTMODE
};

bool normalModeActive;

int checkCmd(char cmd[MAXCHARBUFLEN]);
void runNormalMode();
void printToCmdLine(char* str);

#endif // !NORMALMODE_H
