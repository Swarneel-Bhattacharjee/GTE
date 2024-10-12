#include "scr.h"
#include <ncurses/ncurses.h>
#include "mem.h"
#include <string.h>
#include <stdlib.h>

void insertIntoCurrentLine(char ch) {
    memCharShiftRight();
    lineArr[y]->lineBuf[x] = ch;
    lineArr[y]->currLen ++;
    insch(ch);
    x ++;
    move(y, x);
}

void delPrevChar() {
    memCharShiftLeft();
    x --;
    move(y, x);
    delch();
}

void removeThisLine() {
    memLineShiftUp();
    deleteln();
    y --;
    x = lineArr[y]->currLen - 1;
    move(y, x);
}

void addNewLineUnder() {
    char cpy[MAXCHARBUFLEN];
    int _x = 0;
    memset(cpy, 0, MAXCHARBUFLEN * sizeof(char));

    char c;
    while ((c = lineArr[y]->lineBuf[x]) != 0){
        cpy[_x ++] = c;
        lineArr[y]->lineBuf[x ++] = 0;
    }

    y ++;
    x = 0;
    move(y, x);
    insertln();
    memLineShiftDown();
    lineArr[y] = Line();
    for (int i = 0; i < _x; i ++) {
        insertIntoCurrentLine(cpy[i]);
    }

    x = 0;
    move(y, x);
    nLines ++;
} 

void loadFile(){
    FILE* f = fopen(filename, "r");

    char fileContentBuf[MAXCHARBUFLEN];
    char c;
    memset(fileContentBuf, 0, sizeof(char) * MAXCHARBUFLEN);
    int i = 0;

    lineArr = (line**) malloc (sizeof(line*) * MAXLINEBUFLEN);
    nPossibleLines = MAXLINEBUFLEN;
    for (int k = 0; k < MAXLINEBUFLEN; k ++) {
        lineArr[k] = Line();
    }

    if (!f) {
        printf("File %s not found, cannot read\n", filename);
        return;
    }

    while ((c = getc(f)) != EOF) fileContentBuf[i++] = c;
    fclose(f);

    for (int j = 0; j < i; j ++) {
        c = fileContentBuf[j];
        insertIntoCurrentLine(c);
        if (c == '\n') addNewLineUnder();
    }
}
