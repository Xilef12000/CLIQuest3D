
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buffer {
    unsigned short sX;
    unsigned short sY;
    unsigned long *cur;
    unsigned short *bP;
};

struct dict {
    unsigned short i;
    char *s;
};
#define uniLen 11

struct dict uni[uniLen] = {
    {11000, "\u2588"},
    {11001, "\u2593"},
    {11002, "\u2592"},
    {11003, "\u2591"},
    {12000, "\u2581"},
    {12001, "\u2582"},
    {12002, "\u2583"},
    {12003, "\u2584"},
    {12004, "\u2585"},
    {12005, "\u2586"},
    {12006, "\u2587"},
};

int placeB(unsigned short c, int x, int y, struct buffer fb){
    if (x >= 0 && y >= 0) {
        *fb.cur = fb.sX*x+y;
    }
    if (32 <= c && c <= 126 || 10000 <= c && c <= 20000) {
        fb.bP[*fb.cur] = c;
    }
    else if(c == 10) {
        (*fb.cur)+= fb.sX - ((*fb.cur) % (unsigned long) fb.sX) - 1;
    }
    else {
        fb.bP[*fb.cur] = ' ';
    }
    (*fb.cur)++;
    if ((*fb.cur) >= fb.sX*fb.sY){
        (*fb.cur) = fb.sX*fb.sY-1;
    }
    return 0;
};

int putB(unsigned short c, struct buffer fb){
    return placeB(c, -1, -1, fb);   
};

int printB(char s[], struct buffer fb){
    for (int i = 0; i < strlen(s); i++) {
        putB(s[i], fb);
    }
    return 0;
};

int displayB(struct buffer fb){
    printf("\e[1;1H"); // cursor to top left
    for (int i = 0; i < fb.sY; i++){
        for (int n = 0; n < fb.sX; n++){
            unsigned short c = fb.bP[fb.sX*i+n];
            if (32 <= c && c <= 126) { 
                putc(c, stdout);
            }
            else if (10000 <= c && c <= 20000) { 
                for (int m = 0; m < uniLen; m++){
                    if (uni[m].i == c){
                        printf("%s", uni[m].s);
                        break;
                    }
                }
            }
        }
        fputs("\r\n", stdout);
    }
    (*fb.cur) = 0;
    return 0;
};