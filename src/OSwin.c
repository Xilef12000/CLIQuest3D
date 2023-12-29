#include "crossplatform.h"
#include "framebuffer.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <conio.h>

int EnableVTMode()
{   
    // Set output mode to handle virtual terminal sequences
    DWORD fdwMode, fdwOldMode;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hStdin;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE)
    {
        //printf("hout:%s", hOut);
        return 0;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        printf("dwMode: %s", dwMode);
        return 0;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return 0;
    }

    GetConsoleMode(hStdin, &fdwOldMode);

    fdwMode = fdwOldMode &
        ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    SetConsoleMode(hStdin, fdwMode);
    // Set Codepage
    UINT CP_id = 65001;
    SetConsoleOutputCP(CP_id);
    return 1;

}

int getCliDim(struct buffer fb) {
    EnableVTMode();
    
    HANDLE hStdout;

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

    return 1;
}

int getKeysInBuffer() {
    int inBuffer;
    // how many characters in input buffer
    //inBuffer = scanf("%s", keystr);
    inBuffer = _kbhit();
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