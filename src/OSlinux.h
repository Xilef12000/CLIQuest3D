#ifndef OSLINUX_H_
#define OSLINUX_H_

    #include <sys/ioctl.h>
    #include "OSlinux.c"
    #include "framebuffer.h"

    #define UNILEN 22
    struct dict codes[UNILEN] = {
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
        {12007, "\u259A"}, //wall goal
        {12008, "\u25D9"},  // wall removable
        {13000, "\u2191"},
        {13001, "\u2196"},
        {13002, "\u2190"},
        {13003, "\u2199"},
        {13004, "\u2193"},
        {13005, "\u2198"},
        {13006, "\u2192"},
        {13007, "\u2197"},
    };

    int initOS();
    int getCliDim(int *cliX, int *cliY);
    int getKeysInBuffer();
    char getKey();


#endif // OSLINUX_H_