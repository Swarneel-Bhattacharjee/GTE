#include <string.h>
#include <stdbool.h>
#include "kb.h"
#include "scr.h"
#include "mem.h"
#include <stdlib.h>
#include <ncurses/ncurses.h>


bool handleKeypress() {
    char c = getch();

    switch (c){
        case K_ESC : {
            return false; // false means to stop looping
            break;
        }

        case K_BCKSPC : {
            if (x > 0) delPrevChar(); 
            else {
                if (y == 0) break;
                joinWithPrevLine(); 
            }
            isDirty = true;
            break;
        }

        case K_TAB : {
            insertIntoCurrentLine(' ');
            insertIntoCurrentLine(' ');
            insertIntoCurrentLine(' ');
            insertIntoCurrentLine(' ');
            isDirty = true;
            break;
        }

        case K_RET : {
            insertIntoCurrentLine('\n');
            addNewLineUnder();
            isDirty = true;
            break;
        }

        case K_SPCL : {
            c = getch();
            handleSpclCharPress(c);
            break;
        }

        default : {
            insertIntoCurrentLine(c);
            isDirty = true; 
            break;
        }
    }

    return true; // true means keep looping
}

void handleSpclCharPress(char c) {
    switch (c){
        case K_UP : {
            if (y == 0) { x = 0; break;}
            y --;
            x = min(x, lineArr[y]->currLen - 1);
            break;
        }

        case K_DOWN : {
            if (y >= nLines - 1) { x = lineArr[y]->currLen - 1; break;}
            y ++;
            x = min(x, lineArr[y]->currLen - 1);
            break;
        }

        case K_LEFT : {
            if (x == 0) {
                if (y == 0) break;
                y --;
                x = lineArr[y]->currLen - 1;
            } else x --;
            break;
        }

        case K_RIGHT : {
            if (x >= lineArr[y]->currLen - 1) {
                if (y == nLines) break;
                y ++;
                x = 0;
            } else x ++;
            break;
        }

        case K_DELETE : {
            if (x == lineArr[y]->currLen - 1)  {
                x = 0;
                y ++;
                move(y, x);
                joinWithPrevLine();
            } else {
                x ++;
                delPrevChar();
            }
            break;
        }

        case K_HOME : {
            x = 0;
            break;
        }

        case K_END : {
            x = lineArr[y]->currLen - 1;
            break;
        }

        case K_PGUP :{
            y = 0;
            x = min(x, lineArr[y]->currLen - 1);
            break;
        }

        case K_PGDWN : {
            y = nLines - 1;
            x = min(x, lineArr[y]->currLen - 1);
            break;
        }
    }

    move(y, x);
}
