#ifndef KB_H
#define KB_H

#define K_ESC       27
#define K_TAB       '\t'
#define K_RET       '\n'
#define K_BCKSPC    '\b'
#define K_SPCL      0
#define K_UP        'H'
#define K_RIGHT     'M'
#define K_DOWN      'P'
#define K_LEFT      'K'

void handleKeypress();
void handleSpclCharPress(char c);

#endif  // KB_H