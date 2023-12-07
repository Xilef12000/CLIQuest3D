#include "crossplatform.h"
#include "framebuffer.h"

int getCliDim(struct buffer fb) {
    // get window size in characters

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