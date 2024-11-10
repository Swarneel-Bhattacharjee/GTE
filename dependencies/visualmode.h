#ifndef VISUALMODE_H
#define VISUALMODE_H

#include "mem.h"
#include <stdbool.h>

char* clipboard[MAXCHARBUFLEN];
int startX, startY, endX, endY;

int* highlightX;
int* highlightY;

void select(int starty, int startx, int endy, int endx);
void copySelection();
void cutSelection();
void deleteSelection();
void pasteSelectionOnTop();
void insertSelectionAtXY();
void editSelection(int type);

bool vm_handleVisualmodeInput();
void vm_handleSpclCharPress(char c);

void runVisualMode();

#endif // VISUALMODE_H 
