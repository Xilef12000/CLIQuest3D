#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

    struct buffer { // Buffer
        unsigned short *sX;
        unsigned short *sY;
        unsigned long *cur;
        unsigned short *bP;
    };

    struct dict { // dictionary for special OS dependent Unicode symbols
        unsigned short i;
        char *s;
    };

    int checkBCur(struct buffer fb); // check if cursor is still in Buffer
    int setBCur(int x, int y, struct buffer fb); // set cursor to location in Buffer
    int moveBCur(int n, struct buffer fb); // move cursor n characters
    int placeB(unsigned short c, int x, int y, struct buffer fb); // place character as specific location into Buffer and move cursor forward
    int putB(unsigned short c, struct buffer fb); // put character at cursor into Buffer and move cursor forward
    int printB(char s[], struct buffer fb); // print string at cursor into Buffer and move cursor forward
    int clearB(struct buffer fb); // clear Buffer (fill with spaces)
    int fprintB(struct buffer fb, const char *format, ...); // formated print into Buffer at cursor (like printf() but with output into Buffer)
    int displayB(struct buffer fb, struct dict *codes, unsigned short codesLen); // output whole Buffer into Terminal
    struct buffer init_buffer(int *cliX, int *cliY); // allocate memory needed to store Buffer in RAM (Buffer size depends on screen size)

    #include "framebuffer.c"


#endif // FRAMEBUFFER_H_
