#ifndef OSLINUX_H_
#define OSLINUX_H_

    #include <sys/ioctl.h>
    #include "OSlinux.c"
    #include "framebuffer.h"

    #define UNILEN 26
    struct dict codes[UNILEN] = {
        // wall
        {11000, "\u2588"},
        {11001, "\u2593"},
        {11002, "\u2592"},
        {11003, "\u2591"},
        {11004, " "},
        // floor
        {12000, "\u2581"},
        {12001, "\u2582"},
        {12002, "\u2583"},
        {12003, "\u2584"},
        {12004, "\u2585"},
        {12005, "\u2586"},
        {12006, "\u2587"},

        {12007, "\u259A"}, //wall goal
        {12008, "\u25D9"},  // wall removable

        // minimap
        {13000, "\u2191"},
        {13001, "\u2196"},
        {13002, "\u2190"},
        {13003, "\u2199"},
        {13004, "\u2193"},
        {13005, "\u2198"},
        {13006, "\u2192"},
        {13007, "\u2197"},

        // shoot animation
        {14000, "*"},
        {14001, "#"},
        {14002, "^"},
        {14003, "$"},
    };

    // set console options for output cursor visibility an codepage
    int initOS();

    // get dimensions of console in charaters
    int getCliDim(int *cliX, int *cliY);

    // determine if chars are left from keyboard input
    int getKeysInBuffer();

    // get single key from input buffer
    char getKey();

#endif // OSLINUX_H_