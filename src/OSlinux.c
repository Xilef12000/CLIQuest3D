#include "crossplatform.h"
#include "framebuffer.h"
#include <sys/ioctl.h>
#include <stdio.h>

int initOS(){
    // set console options
    printf("\e[1;1H\e[2J"); // cursor to top left of page and clear page
    
    return 1;
}


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
