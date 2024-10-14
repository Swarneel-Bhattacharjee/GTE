#include <string.h>
#include "kb.h"
#include "scr.h"
#include "mem.h"
#include <stdlib.h>
#include <ncurses/ncurses.h>

void handleKeypress() {
    char c = getch();

    switch (c){
        case K_ESC : {
            writeFile();
            clearMem();
            endwin();
            exit(0);
            break;
        }

        case K_BCKSPC : {
            if (x > 0) delPrevChar();
            else removeThisLine();
            break;
        }

        case K_TAB : {
            insertIntoCurrentLine(' ');
            insertIntoCurrentLine(' ');
            insertIntoCurrentLine(' ');
            insertIntoCurrentLine(' ');
            break;
        }

        case K_RET : {
            insertIntoCurrentLine('\n');
            addNewLineUnder();
            break;
        }

        case K_SPCL : {
            c = getch();
            handleSpclCharPress(c);
            break;
        }

        default : {
            insertIntoCurrentLine(c);
            break;
        }
    }
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
            if (y >= nLines) x = lineArr[y]->currLen - 1;
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
            if (x >= lineArr[y]->currLen - 1) {
              if (y >= nLines - 1) break;
              else {
                // Remove the newline character
                x ++;
                memCharShiftLeft();
                x --;
                
                // Copy the line underneath
                char cpy[MAXCHARBUFLEN];
                memset(cpy, 0, sizeof(char) * MAXCHARBUFLEN);
                y ++;
                int x_ = 0;
                char c;
                while ((c = lineArr[y]->lineBuf[x_]) != 0){
                  cpy[x_ ++] = c;
                }

                // Remove the lower line
                removeThisLine();
                
                x_ = 0;
                // paste the copied contents at the end of this line
                while ((c = cpy[x_++]) != 0) {
                  insertIntoCurrentLine(c);
                }
              }
            } else {
                delch();
                x ++;
                memCharShiftLeft();
                x --;
                lineArr[y]->currLen - 1;
                break;
            }
        }
    }

    move(y, x);
}
