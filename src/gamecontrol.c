#include "gamecontrol.h"
#include "draw.h"

struct position kb_control(struct position player_loc)
{
    struct position new;
    new = player_loc;
    int key = getKey(); // get character

    if (!isMenu){
        float pRad = player_loc.pA*M_PI/180; // degree to radians
        switch (key) {
            // rotate or walk according to key press, exit if '.'
            case 'w':
                new.pX += sin(pRad)*stepXY;
                new.pY += cos(pRad)*stepXY;
                break;
            case 'a':
                player_loc.pA+=stepA;
                break;
            case 's':
                new.pX -= sin(pRad)*stepXY;
                new.pY -= cos(pRad)*stepXY;
                break;
            case 'd':
                player_loc.pA-=stepA;
                break;
            case 'e':
                if (shoot_cool == 0){
                    lvl.ammo--;
                    shoot = 1.0/((float) tTaken / 1000)*100;
                    shoot_cool = shoot*shoot_factor + 2;
                    shoot += 10;
                    shoot_dur = shoot;
                    if (lvl.ammo < 0) {
                        lvl.ammo = -1;
                        shoot = 0;
                        shoot_cool = shoot_cool/2;
                    }
                }
                break;
            case  '.':
                isMenu = 1;
                break;
        }
    }
    else {
        switch (key) {
            case '.':
                loop = 0;
                break;
            case ' ':
                isMenu = 0;
                break;
        }
    }
    // check if theoretical new position is not in wall -> write it to current position
    // separate check for walk along wall
    if(lvl.world[(int)(player_loc.pY)][(int)new.pX] == 0) {
        player_loc.pX = new.pX;
    }
    if(lvl.world[(int)(new.pY)][(int)player_loc.pX] == 0) {
        player_loc.pY = new.pY;
    }
    return player_loc;
}

void start_fps() {
    // variables for time stats
    frame = 0;
    gettimeofday(&tLast, NULL);
}
void calc_fps(struct buffer fb) {
    // calculate and output time stats
    gettimeofday(&tNow, NULL);
    tTaken = (tNow.tv_sec - tLast.tv_sec) * 1000000 + tNow.tv_usec - tLast.tv_usec;
    draw_fps(fb, (float) tTaken / 1000, (float) 1.0/tTaken*1000000, frame);
    tLast = tNow;
    frame++;
}