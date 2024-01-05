#include "draw.h"

int map(int x, int inMin, int inMax, int outMin, int outMax) {
    // mapping function of one int in range to int in other range
    int n = (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    if (n > outMax) n = outMax;
    if (n < outMin) n = outMin;
    return n;
}

void draw_3d(unsigned short distance[cliX][2], struct buffer fb)
{
    for (int i = 0; i < cliY; i++) { //for every horizontal line of output image
        for (int j = cliX-1; j >= 0; j--) { // for every pixel in horizontal line
            if (cliY/2-(cliY-map(distance[j][0],0,maxVDist,0,cliY))/2 <= i) { // if pixel is not ceiling -> wall or floor
                if (cliY/2+(cliY-map(distance[j][0],0,maxVDist,0,cliY))/2 >= i) { // if pixel is not floor -> wall
                    // draw gray shade depending on distance of wall to player
                    if (distance[j][0] < maxVDist*0.25){
                        switch (distance[j][1])
                        {
                        case 1:
                            putB(11000, fb);
                            break;
                        case 2:
                            putB(11000, fb);
                            break;
                        } 
                    }
                    else if (distance[j][0] < maxVDist*0.5){
                        putB(11001, fb);
                    }
                    else if (distance[j][0] < maxVDist*0.75){
                        putB(11002, fb);
                    }
                    else if (distance[j][0] < maxVDist){
                        putB(11003, fb);
                    }   
                    else {
                        putB(11004, fb);
                    }
                }
                else { // -> pixel is floor
                    //  draw gray shade depending on distance of floor to player
                    if (i < cliY/2/7*1){
                        putB(12000, fb);
                    }
                    else if (i < cliY/2+cliY/2/7*2){
                        putB(12001, fb);
                    }
                    else if (i < cliY/2+cliY/2/7*3){
                        putB(12002, fb);
                    }
                    else if (i < cliY/2+cliY/2/7*4){
                        putB(12003, fb);
                    }
                    else if (i < cliY/2+cliY/2/7*5){
                        putB(12004, fb);
                    }
                    else if (i < cliY/2+cliY/2/7*6){
                        putB(12005, fb);
                    }
                    else {
                        putB(12006, fb);
                    }
                }
            }
            else { // -> pixel is ceiling
                putB(' ', fb); // empty pixel
            }
        }
        putB('\n', fb); // cursor to new line after end of horizontal line 
    } 
}

void draw_map(struct position player, struct buffer fb){
    // draw map
    setBCur(0, 1, fb); //reset cursor to top left corner
    short mY1 = player.pY-(float)mapS/2;
    mY1 = mY1 > 0 ? mY1 : 0;
    short mY2 = mY1 == 0 ? mY1+mapS : player.pY+(float)mapS/2;
    mY2 = mY2 < WORLDSIZE ? mY2 : WORLDSIZE;
    mY1 = mY2 != WORLDSIZE ? mY1 : mY2-mapS;
    short mX1 = player.pX-(float)mapS/2;
    mX1 = mX1 > 0 ? mX1 : 0;
    short mX2 = mX1 == 0 ? mX1+mapS : player.pX+(float)mapS/2;
    mX2 = mX2 < WORLDSIZE ? mX2 : WORLDSIZE;
    mX1 = mX2 != WORLDSIZE ? mX1 : mX2-mapS;
    for (int i = 0; i < mapS+1; i++) {
        putB('+', fb);
        if (i != mapS) {
            putB(' ', fb);
        }
    };
    putB('\n', fb);
    for (int i = mY1; i < mY2; i++){
        putB('+', fb);
        for (int j = mX1; j < mX2; j++){
            if (j != mX1) {
                putB(' ', fb);
            }
            if (lvl.world[i][j] == 1) {
                putB('#', fb);
            }
            else {
                putB(' ', fb);
            }
        }
        putB('+', fb);
        putB('\n', fb);
    }
    for (int i = 0; i < mapS+1; i++) {
        putB('+', fb);
        if (i != mapS) {
            putB(' ', fb);
        }
    };
    setBCur((int)player.pX*2-mX1*2, player.pY-mY1+2, fb);
    switch (map(((((int)(player.pA-180+22.5) % 360)+360) % 360), 0, 360, 0, 8)) {
        case 0:
            putB(13000, fb);
            break;
        case 1:
            putB(13001, fb);
            break;
        case 2:
            putB(13002, fb);
            break;
        case 3:
            putB(13003, fb);
            break;
        case 4:
            putB(13004, fb);
            break;
        case 5:
            putB(13005, fb);
            break;
        case 6:
            putB(13006, fb);
            break;
        case 7:
            putB(13007, fb);
            break;
    }
}
void draw_menu(struct buffer fb)
{
    clearB(fb);
    setBCur(0, 3, fb);

    for (int i = 0; i < 8; i++) {
        printB((char*)logo[i], fb);
        putB('\n', fb);
    }

    for (int i = 0; i < 8; i++) {
        printB((char*)credits[i], fb);
    }
 }

void ray_cast(struct position player_loc, unsigned short distance[cliX][2]){
    // ray casting:
    // draw lines from player_loc in every direction in view
    // lines can only be drawn between between to points
    // point one: player_loc, and point two a pointer outside of world so it can never be reached
    // the line is drawn in small steps from the first to the second point
    for (int i = 0; i < cliX; i++) {
        float l = 0; // line step counter
        float x1 = player_loc.pY; // point one = player_loc position
        float y1 = player_loc.pX;
        // line degree in radiens (looking direction - half pov + line offset)
        float srad = (((player_loc.pA - (double) fov / 2) + (i * cliA)) * M_PI) / 180;
        float y2 = y1+(sin(srad)*WORLDSIZE+1); // calculate point two
        float x2 = x1+(cos(srad)*WORLDSIZE+1);

        float dx =  fabs(x2 - x1); // delta between x1 and x2
        float sx = x1<x2 ? 0.1 : -0.1; // direction of x delta -> x step
        float dy = -fabs(y2 - y1); // delta between y1 and y2
        float sy = y1<y2 ? 0.1 : -0.1; // direction of y delta -> y step
        float err = dx+dy, e2;

        int iswall = lvl.world[(int)x1][(int)y1];
        while (iswall == 0) {
            iswall = lvl.world[(int)x1][(int)y1];

            l++; // next distance step
            e2 = 2*err;

            // determine if this step should be done on x or y axis -> increase error (difference to ideal line) and make step 
            if (e2 >= dy) {
                err += dy; 
                x1 += sx;
            }
            else if (e2 <= dx) {
                err += dx; 
                y1 += sy;
            }  
            
        }

        distance[i][0] = l/10; // safe distance to wall (number of necessary steps)
        distance[i][1] = iswall; //walltype

    }
}
