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
    lineArr[y]->currLen --;
}

void joinWithPrevLine() {
    // Copy the remaining line
    char cpy[MAXCHARBUFLEN];
    memset(cpy, 0, sizeof(char) * MAXCHARBUFLEN);
    int i = x;
    char c;
    while ((c = lineArr[y]->lineBuf[i]) != 0) cpy[i++] = c;

    //delete this line
    y ++;
    memLineShiftUp();
    nLines --;
    y --;
    deleteln();
    y --;
    x = lineArr[y]->currLen - 1;

    // Join the content from last \n character (included) to the end of the lineo
    x++;
    delPrevChar();
    int x_ = x;
    for (int j = 0; j < i; j ++) insertIntoCurrentLine(cpy[j]);

    // Move cursor back to where the last newLine character should have been
    x = x_;
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
