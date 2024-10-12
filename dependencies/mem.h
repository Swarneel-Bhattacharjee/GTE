#ifndef MEM_H
#define MEM_H

#define min(a, b) ((a < b)? a : b)
#define max(a, b) ((a > b)? a : b)

#define MAXCHARBUFLEN 1000
#define MAXLINEBUFLEN 1000

typedef struct Line{
    int allocdSize;
    int currLen;    // Includes newline character in mem
    char* lineBuf;
} line;

char* filename;
int isDirty;

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

void writeFile();
void clearMem();

#endif