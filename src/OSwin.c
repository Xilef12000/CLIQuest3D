#include "crossplatform.h"
#include "framebuffer.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <conio.h>

int initOS()
{   
    // Set output mode to handle virtual terminal sequences
    DWORD fdwMode, fdwOldMode;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hStdin;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    hOut == INVALID_HANDLE_VALUE;

    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    GetConsoleMode(hStdin, &fdwOldMode);

    fdwMode = fdwOldMode &
        ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    SetConsoleMode(hStdin, fdwMode);
    
    // Set Codepage
    // propper font type has to be selected in terminal options manually
    UINT CP_id = 65001;
    SetConsoleOutputCP(CP_id);

    printf("\e[1;1H\e[2J"); // cursor to top left of page and clear page

    return 1;

}

int getCliDim(int *cliX, int *cliY) {
    HANDLE hStdout;

    // get window size in characters
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    SMALL_RECT srctWindow;

    // Get the current screen buffer size and window position.
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo);

    // Set srctWindow to the current window size and location.
    srctWindow = csbiInfo.srWindow;

    (*cliX) = srctWindow.Right - srctWindow.Left;
    (*cliY) = srctWindow.Bottom - srctWindow.Top;

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