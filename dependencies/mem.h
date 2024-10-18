#ifndef MEM_H
#define MEM_H

#include <stdbool.h>

#define min(a, b) ((a < b)? a : b)
#define max(a, b) ((a > b)? a : b)

#define MAXCHARBUFLEN 1000
#define MAXLINEBUFLEN 1000

#define STATE_NORMALMODE 0
#define STATE_INPUTMODE 1 


typedef struct Line{
    int allocdSize;
    int currLen;    // Includes newline character in mem
    char* lineBuf;
} line;


int terminal_max_x;
int terminal_max_y;


char* filename;
bool isDirty;
bool isRunning;
int currentMode;

int x;
int y;
int nLines;
int nPossibleLines;

line** lineArr;

line* Line();

void memLineShiftUp();
void memLineShiftDown();
void memCharShiftRight();
void memCharShiftLeft();

void loadFile();
void writeFile();
void clearMem();

#endif
