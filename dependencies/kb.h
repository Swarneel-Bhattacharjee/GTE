#ifndef KB_H
#define KB_H

#define K_ESC       27
#define K_TAB       9 
#define K_RET       10
#define K_BCKSPC    8
#define K_SPCL      0
#define K_UP        'H'
#define K_RIGHT     'M'
#define K_DOWN      'P'
#define K_LEFT      'K'
#define K_DELETE    'S'
#define K_HOME      'G'
#define K_END       'O'
#define K_PGUP      'I'
#define K_PGDWN     'Q'
#define CTRL_Z      26
#define CTRL_X      24
#define CTRL_C      3


enum ASCII {
    NUL, //Null character
    SOH, //Start of Heading,
    STX, //Start of Text,
    ETX, //End of Text,
    EOT, //End of Transmission
    ENQ, //Enquiry
    ACK, //bAcknowledge
    BEL, //Bell, Alert
    BS, //Backspace
    HT, //Horizontal Tab
    LF, //Line Feed
    VT, //Vertical Tabulation
    FF, //Form Feed
    CR, //Carriage Return
    SO, //Shift Out
    SI, //Shift In
    DLE, //Data Link Escape
    DC1, //Device Control One (XON)
    DC2, //Device Control Two
    DC3, //Device Control Three (XOFF)
    DC4, //Device Control Four
    NAK, //Negative Acknowledge
    SYN, //Synchronous Idle
    ETB, //End of Transmission Block
    CAN, //Cancel
    EM, //End of medium
    SUB, //Substitute
    ESC, //Escape
    FS, //File Separator
    GS, //Group Separator
    RS, //Record Separator
    US, //Unit Separator
};

bool handleKeypress();
void handleSpclCharPress(char c);

#endif  // KB_H
