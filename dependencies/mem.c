#include "mem.h"
#include <ncurses/ncurses.h>
#include <string.h>
#include <stdlib.h>

line* Line() {
    line* l = (line*) malloc (sizeof(line) * 1);
    l->allocdSize = MAXCHARBUFLEN;
    l->currLen = 0;
    l->lineBuf = (char*) malloc (sizeof(char) * MAXCHARBUFLEN);
    memset(l->lineBuf, 0, sizeof(char) * l->allocdSize);
    return l;
}

void makeLines(char* fileContentBuf) {
    int j = 0;
    char c = -1;

    while ((c = fileContentBuf[j++]) != 0) {
        lineArr[y]->lineBuf[x++] = c;
        lineArr[y]->currLen ++;
        if (c == '\n') {
            y ++;
            x = 0;
            nLines ++;
        }
    }
}


void loadFile() {
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

    makeLines(fileContentBuf); 

    return;
}

void writeFile(){
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Couldn't open file %s to write\n", filename);
        return;
    }
    
    for (int i = 0; i <= nLines; i ++) {    // the = sign should logically not be here
        fprintf(f, "%s", lineArr[i]->lineBuf);
    }
    
    isDirty = false;
    fclose(f);
}

void clearMem() {
    for (int i = 0; i < nPossibleLines; i ++) {
        free(lineArr[i]->lineBuf);
        free(lineArr[y]);
    }
    free(lineArr);
}

void memLineShiftUp(){
    if (y == 0) {
        printf("Cannot shift up, y = 0\n");
        return;
    }

    for (int i = y; i < nPossibleLines - 1; i ++) {
        lineArr[i-1] = lineArr[i];
    }
}

void memLineShiftDown(){
    if (y > nPossibleLines - 2) {
        printf("Cannot shift down, y >= nPossibleLines - 2\n");
        return;
    }

    line* a = lineArr[y];
    line* b = lineArr[y + 1];
    for (int i = y + 1; i < nPossibleLines - 2; i ++) {
        lineArr[i] = a;
        a = b;
        b = lineArr[i + 1];
    }
}

void memCharShiftLeft(){
    if (x == 0){
        printf("Cannot shift, x = 0\n");
        return;
    }

    for (int i = x; i < lineArr[y]->allocdSize - 1; i ++){
        lineArr[y]->lineBuf[i - 1] = lineArr[y]->lineBuf[i];
    }
}

void memCharShiftRight(){
    if (x == lineArr[y]->allocdSize - 1) {
        printf("Cannot shift right, x = allocdSize - 1\n");
        return;
    }

    char a = lineArr[y]->lineBuf[x];
    char b = lineArr[y]->lineBuf[x + 1];
    for (int i = x + 1; i < lineArr[y]->allocdSize - 2; i ++){
        lineArr[y]->lineBuf[i] = a;
        a = b;
        b = lineArr[y]->lineBuf[i + 1];
    }
}
