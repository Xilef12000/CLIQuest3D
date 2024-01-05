#ifndef GAMECONTROL_H_
#define GAMECONTROL_H_
/*
*/
    #include <math.h>
    #define _USE_MATH_DEFINES
    #include "draw.h"
    #include "gamecontrol.c"

    struct position kb_control(struct position player_loc);

#endif //GAMECONTROL_H_