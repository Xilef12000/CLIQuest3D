#include "crossplatform.h"
#include "framebuffer.h"
#include <windows.h>
#include <stdio.h>

HANDLE hStdout;


int getCliDim(struct buffer fb) {
    // get window size in characters
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    SMALL_RECT srctWindow;

    // Get the current screen buffer size and window position.
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo);

    // Set srctWindow to the current window size and location.
    srctWindow = csbiInfo.srWindow;

    (*fb.sX) = srctWindow.Right - srctWindow.Left;
    (*fb.sY) = srctWindow.Bottom - srctWindow.Top;

    return 0;
}

int getKeysInBuffer() {
    int inBuffer;
    // how many characters in input buffer
    return inBuffer;
}

char getKey() {
    return getchar();
}

int setCodes(struct dict *codes, unsigned short codesLen) {
    #define UNILEN 11
    struct dict uni[UNILEN] = {
        {11000, ""},
        {11001, ""},
        {11002, ""},
        {11003, ""},
        {12000, ""},
        {12001, ""},
        {12002, ""},
        {12003, ""},
        {12004, ""},
        {12005, ""},
        {12006, ""},
    };
    for (int i = 0; i < ((UNILEN > codesLen) ? codesLen : UNILEN); i ++) {
        codes[i].i = uni[i].i;
        codes[i].s = uni[i].s;
    }
    return 0;
}