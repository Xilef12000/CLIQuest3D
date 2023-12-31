#include "crossplatform.h"
#include "framebuffer.h"
#include <sys/ioctl.h>
#include <stdio.h>

int getCliDim(struct buffer fb) {
    // get window size in characters
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    (*fb.sY) = w.ws_row - 1;
    (*fb.sX) = w.ws_col - 1;
    return 1;
}

int getKeysInBuffer() {
    int inBuffer;
    ioctl(0, FIONREAD, &inBuffer); // how many characters in input buffer
    return inBuffer;
}

char getKey() {
    return getchar();
}

int setCodes(struct dict *codes, unsigned short codesLen) {
    #define UNILEN 20
    struct dict uni[UNILEN] = {
        {11000, "\u2588"},
        {11001, "\u2593"},
        {11002, "\u2592"},
        {11003, "\u2591"},
        {11004, " "},
        {12000, "\u2581"},
        {12001, "\u2582"},
        {12002, "\u2583"},
        {12003, "\u2584"},
        {12004, "\u2585"},
        {12005, "\u2586"},
        {12006, "\u2587"},
        {13000, "\u2191"},
        {13001, "\u2196"},
        {13002, "\u2190"},
        {13003, "\u2199"},
        {13004, "\u2193"},
        {13005, "\u2198"},
        {13006, "\u2192"},
        {13007, "\u2197"},
    };
    for (int i = 0; i < ((UNILEN > codesLen) ? codesLen : UNILEN); i ++) {
        codes[i].i = uni[i].i;
        codes[i].s = uni[i].s;
    }
    return 0;
}