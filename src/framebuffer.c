#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "crossplatform.h"

struct buffer {
    unsigned short *sX;
    unsigned short *sY;
    unsigned long *cur;
    unsigned short *bP;
};
struct dict {
    unsigned short i;
    char *s;
};

int checkBCur(struct buffer fb){
    if ((*fb.cur) >= (*fb.sX)*(*fb.sY)){
        (*fb.cur) = (*fb.sX)*(*fb.sY)-1;
    }
    return 0;
};
int setBCur(int x, int y, struct buffer fb){
    *fb.cur = (*fb.sX)*y+x;
    checkBCur(fb);
    return 0;
};
int moveBCur(int n, struct buffer fb){
    *fb.cur += n;
    checkBCur(fb);
    return 0;
};
int placeB(unsigned short c, int x, int y, struct buffer fb){
    if (x >= 0 && y >= 0) {
        setBCur(x, y, fb);
    }
    if (32 <= c && c <= 126 || 10000 <= c && c <= 20000) {
        fb.bP[*fb.cur] = c;
    }
    else if(c == 10) { //new line
        moveBCur((*fb.sX) - ((*fb.cur) % (unsigned long) (*fb.sX)) - 1, fb);
    }
    else {
        fb.bP[*fb.cur] = ' ';
    }
    moveBCur(1, fb);
    if ((*fb.cur) >= (*fb.sX)*(*fb.sY)){
        setBCur((*fb.sX), (*fb.sY), fb);
    }
    return 0;
};
int putB(unsigned short c, struct buffer fb){
    return placeB(c, -1, -1, fb);   
};
int printB(char s[], struct buffer fb){
    int n;
    for (int i = 0; i < strlen(s); i++) {
        n += putB(s[i], fb);
    }
    return n;
};
int fprintB(struct buffer fb, const char *format, ...){
    va_list args0;
    va_start(args0, format);
    int n = vsnprintf(NULL, 0, format, args0);
    va_end(args0);
    char str[n+1];
    va_list args1;
    va_start(args1, format);
    vsprintf(str, format, args1);
    va_end(args1);
    printB(str, fb);
    return(0);
};
int displayB(struct buffer fb, struct dict *codes, unsigned short codesLen){
    printf("\e[1;1H"); // cursor to top left
    for (int i = 0; i < (*fb.sY); i++){
        for (int n = 0; n < (*fb.sX); n++){
            unsigned short c = fb.bP[(*fb.sX)*i+n];
            if (32 <= c && c <= 126) { 
                putc(c, stdout);
            }
            else if (10000 <= c && c <= 20000) { 
                for (int m = 0; m < codesLen; m++){
                    if (codes[m].i == c){
                        printf("%s", codes[m].s);
                        break;
                    }
                }
            }
        }
        fputs("\r\n", stdout);
    }
    setBCur(0, 0, fb);
    return 0;
};
