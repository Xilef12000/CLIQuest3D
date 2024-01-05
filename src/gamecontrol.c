#include "gamecontrol.h"

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