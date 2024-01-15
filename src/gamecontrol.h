#ifndef GAMECONTROL_H_
#define GAMECONTROL_H_
/*
*/
    #include <math.h>
    #define _USE_MATH_DEFINES
    #include "draw.h"
    #include "gamecontrol.c"
    #include <sys/time.h>
    
    struct position kb_control(struct position player_loc);

#endif //GAMECONTROL_H_

// variables for time stats
struct timeval tNow, tLast;
unsigned long tTaken, frame;

void start_fps();
void calc_fps(struct buffer fb);