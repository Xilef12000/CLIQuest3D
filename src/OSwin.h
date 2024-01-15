#ifndef OSWIN_H_
#define OSWIN_H_

    #define _USE_MATH_DEFINES
    #include "OSwin.c"
    #include "framebuffer.h"

    #define UNILEN 23
    struct dict codes[UNILEN] = {
        {11000, "\u2588"},
        {11001, "\u2593"},
        {11002, "\u2592"},
        {11003, "\u2591"},
        {11004, " "},
        {12000, "\x2E"},
        {12001, "\x2D"},
        {12002, "\x2D"},
        {12003, "\x3D"},
        {12004, "\x3D"},
        {12005, "\u2261"},
        {12006, "\u2261"},
        {12007, "\u25D9"}, //wall goal
        {12008, "\u2592"},  // wall removable
        {13000, "\u2191"},
        {13001, "\u2196"},
        {13002, "\u2190"},
        {13003, "\u2199"},
        {13004, "\u2193"},
        {13005, "\u2198"},
        {13006, "\u2192"},
        {13007, "\u2197"},
        {14000, "*"},
    };

    int initOS();
    int getCliDim(int *cliX, int *cliY);
    int getKeysInBuffer();
    char getKey();

#endif // OSWIN_H_