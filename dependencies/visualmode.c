#include "visualmode.h"
#include <ncurses/ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mem.h"
#include "kb.h"
#include "scr.h"


#define FLIP_COLOR(attrib, color) {\
    if (color == 1 || color == 0) {\
        chgat(1, 0, 2, NULL);\
    } else if (color == 2) {\
        chgat(1, 0, 1, NULL);\
    }\
    refresh();\
}


/*
 * For highlighting, first find out the start and the end, then highlight
 * Also need to track whether highlighting should be normal to reverse or reverse to normal
*/

void runVisualMode() {
    bool visualmode_active =  true;

    highlightX = (int*) malloc((1 + terminal_max_x) * sizeof(int));
    highlightY = (int*) malloc((1 + terminal_max_y) * sizeof(int));

    int y_ = terminal_max_y;
    int x_ = 6;
    move(y_, x_);
    clrtoeol();
    printw("VISUALMODE");
    move(y, x);
    while (visualmode_active) {
        visualmode_active = vm_handleVisualmodeInput();
        //select(y, x, endY, endX);
    }

    currentMode = STATE_NORMALMODE;

    for (int y_ = 0; y_ < terminal_max_y; y_ ++) {
        for (int x_ = 0; x_ < terminal_max_x; x_ ++){
            move(y_, x_);
            chgat(1, 0, 0, NULL);
        }
    }
}


bool vm_handleVisualmodeInput() {
    char c = getch();

    attr_t attrib;
    short color;
    chtype ch;

    startX = x;
    startY = y;

    switch (c){
        case K_ESC : {
            return false; // false means to stop looping
            break;
        }

        case K_BCKSPC : {
            // After finding starting and ending coords, highlight them
            break;
        }

        case K_TAB : {  // Should highlight till the next word, but for now will only move forward 4 characters
            break;
        }

        case K_RET : {  // Highlight the entire line till end and move cursor to start of next line
            break;
        }

        case K_SPCL : {
            c = getch();
            vm_handleSpclCharPress(c);
            break;
        }

        default : {
            break;
        }
    }

    endX = startX;
    endY = startY;
    return true;
}


void select(int starty, int startx, int endy, int endx){
}


void vm_handleSpclCharPress(char c) {
    attr_t attrib;
    short color;
    chtype ch;

    switch (c){
        case 'k' :
        case K_UP : { // Highlight till the beginning of the line. Then highlight till the cursor x but one line above from left
            int x_ = x;

            while (x > 0) {
                x --;
                move(y, x);
                ch = winch(stdscr);
                attrib = ch & A_ATTRIBUTES;
                color = PAIR_NUMBER(ch & A_COLOR);
                FLIP_COLOR(attrib, color);
                *(highlightX ++) = x;
                *(highlightY ++) = y;
            }

            if (y == 0) break;
            else {
                y --;
                x = lineArr[y]->currLen-1;

                if (x < x_) break;
                else {
                    while (x > x_) {
                        x --;
                        move(y, x);
                        ch = winch(stdscr);
                        attrib = ch & A_ATTRIBUTES;
                        color = PAIR_NUMBER(ch & A_COLOR);
                        FLIP_COLOR(attrib, color);

                        *(highlightX ++) = x;
                        *(highlightY ++) = y;
                    }
                }
            }

            break;
        }

        case 'j' :
        case K_DOWN : { // Highlight till end of line, then till old x-posn in next line
            int x_ = x; 
            while (x < lineArr[y]->currLen-1) {
                ch = winch(stdscr);
                attrib = ch & A_ATTRIBUTES;
                color = PAIR_NUMBER(ch & A_COLOR);
                FLIP_COLOR(attrib, color);
                *(highlightX ++) = x;
                *(highlightY ++) = y;
                x++;
                move(y, x);
            }

            if (y == nLines) break;
            else {
                y++;
                x = 0;
                move(y, x);

                while (x < min(x_, lineArr[y]->currLen-1)) {
                    ch = winch(stdscr);
                    attrib = ch & A_ATTRIBUTES;
                    color = PAIR_NUMBER(ch & A_COLOR);
                    FLIP_COLOR(attrib, color);
                    *(highlightX ++) = x;
                    *(highlightY ++) = y;
                    x++;
                    move(y, x);
                }
            }

            break;
        }

        case 'h' :
        case K_LEFT : { // Highlight this character and move to previous character
           if (x == 0){
                if (y == 0) break;
                else {
                    y --;
                    x = lineArr[y]->currLen-1;
                }
            } else x--;
            move(y, x);

            ch = winch(stdscr);
            attrib = ch & A_ATTRIBUTES;
            color = PAIR_NUMBER(ch & A_COLOR);
            FLIP_COLOR(attrib, color);
            *(highlightX ++) = x;
            *(highlightY ++) = y;
            break;
        }

        case 'l' :
        case K_RIGHT : { // Highlight this character and move to next character
            ch = winch(stdscr);
            attrib = ch & A_ATTRIBUTES;
            color = PAIR_NUMBER(ch & A_COLOR);
            FLIP_COLOR(attrib, color);
            *(highlightX ++) = x;
            *(highlightY ++) = y;
            if (x == lineArr[y]->currLen-1){
                if (y == nLines) break;
                else {
                    x = 0;
                    y++;
                }
            } else x++;
            move(y, x);

            break;
        }

        case K_END : {  // Highlight till the end of this line
            break;
        }

        case K_PGUP :{  // To implement later when scrolling starts working
            break;
        }

        case K_PGDWN : {  // To implement later when scrolling starts working
            break;
        }

        default: {
            break;
        }
    }
}

void copySelection() {

}

void pasteSelection() {

}

void cutSelection() {

}

void deleteSelection() {

}

void insertSelectionAtXY() {

}

void editSelection(int type) {

}

