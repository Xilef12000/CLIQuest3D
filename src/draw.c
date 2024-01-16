#include "draw.h"
#include <math.h>
#include <stdlib.h>

int map(int x, int inMin, int inMax, int outMin, int outMax) {
    // mapping function of one int in range to int in other range
    int n = (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    if (n > outMax) n = outMax;
    if (n < outMin) n = outMin;
    return n;
}
float mapf(float x, float inMin, float inMax, float outMin, float outMax) {
    // mapping function of one int in range to int in other range
    float n = (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    if (n > outMax) n = outMax;
    if (n < outMin) n = outMin;
    return n;
}
float pythf(float a, float b){
    // Pythagorean theorem
    return (sqrtf(powf(a, 2) + powf(b, 2)));
}

void draw_3d(struct distance *distance, struct buffer fb)
{
    for (int i = 0; i < cliY; i++) { //for every horizontal line of output image
        for (int j = cliX-1; j >= 0; j--) { // for every pixel in horizontal line
            if (cliY/2-(cliY-map(distance[j].distance,0,maxVDist,0,cliY))/2 <= i) { // if pixel is not ceiling -> wall or floor
                if (cliY/2+(cliY-map(distance[j].distance,0,maxVDist,0,cliY))/2 >= i) { // if pixel is not floor -> wall
                    // draw gray shade depending on distance of wall to player
                    if (distance[j].distance < maxVDist*0.25){
                        switch (distance[j].walltype)
                        {
                        case 1:
                        default:
                            putB(11000, fb);
                            break;
                        case 2:
                            putB(12007, fb);
                            break;
                        case 3:
                            putB(12008, fb);
                            break;
                        } 
                    }
                    else if (distance[j].distance < maxVDist*0.5){
                        putB(11001, fb);
                    }
                    else if (distance[j].distance < maxVDist*0.75){
                        putB(11002, fb);
                    }
                    else if (distance[j].distance < maxVDist){
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
            if (lvl.world[i][j] > 0) {
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
    draw_shoot_cooldown(fb);
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

void ray_cast(struct position player, struct distance *distance){
    // ray casting:
    // draw lines from player in every direction in view
    // lines can only be drawn between between to points
    // point one: player, and point two a pointer outside of world so it can never be reached
    // the line is drawn in small steps from the first to the second point
    for (int i = 0; i < cliX; i++) {
        float l = 0; // line step counter
        float x1 = player.pY; // point one = player position
        float y1 = player.pX;
        // line degree in radiens (looking direction - half pov + line offset)
        float srad = (((player.pA - (double) fov / 2) + (i * cliA)) * M_PI) / 180;
        float y2 = y1+(sin(srad)*WORLDSIZE+1); // calculate point two
        float x2 = x1+(cos(srad)*WORLDSIZE+1);

        float dx =  fabs(x2 - x1); // delta between x1 and x2
        float sx = x1<x2 ? 0.1 : -0.1; // direction of x delta -> x step
        float dy = -fabs(y2 - y1); // delta between y1 and y2
        float sy = y1<y2 ? 0.1 : -0.1; // direction of y delta -> y step
        float err = dx+dy, e2;

        unsigned short iswall = lvl.world[(int)x1][(int)y1];
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
        if (i == cliX/2 && shoot > 0 && shoot == shoot_dur && lvl.world[(int)x1][(int)y1] == 3){
            lvl.world[(int)x1][(int)y1] = 0; // if center line AND shoot AND shootable wall THEN replace wall
        }

        distance[i].distance = l/10; // safe distance to wall (number of necessary steps)
        distance[i].walltype = iswall; //walltype

    }
}

void draw_fps(struct buffer fb, float time, float fps, unsigned long frame){
    setBCur(0, cliY+2, fb);
    fprintB(fb, "time: %10.4f ms; fps: %10.0f; frame: %10.0lu; \n", time, fps, frame); 
}

void draw_shoot(struct buffer fb){
    // some raycasting to draw circle;
    float radius = pythf(cliX-4, cliY-4)*mapf(shoot, shoot_dur, 0.0, 0.0, 1.0)*2;
    float radius_inner = 0;
    if (shoot < shoot_dur/2){
        radius_inner = pythf(cliX-4, cliY-4)*mapf(shoot, (float)shoot_dur/2, 0.0, 0.0, 1.0)/2;
    }
    
    for (int i = 0; i < 720; i++) {
        float x0 = (float)cliX/2;
        float y0 = (float)cliY/2;
        float x1 = x0; // point one = screne center
        float y1 = y0;
        float srad = ((float)i/2 * M_PI) / 180;
        float y2 = y1+(sin(srad)*radius); // calculate point two
        float x2 = x1+(cos(srad)*radius);

        float dx =  fabs(x2 - x1); // delta between x1 and x2
        float sx = x1<x2 ? 1 : -1; // direction of x delta -> x step
        float dy = -fabs(y2 - y1); // delta between y1 and y2
        float sy = y1<y2 ? 1 : -1; // direction of y delta -> y step
        float err = dx+dy, e2;
        while (pythf((x1-x0)/2, y1-y0) <= radius) {
            int x = (int)x1;
            int y = (int)y1;
            if (x >= 0 && x <= cliX-1 && y >= 1 && y <=cliY){
                if (pythf((x1-x0)/2, y1-y0) >= radius_inner){
                    setBCur(x, y, fb);
                    putB(14000 + rand() % 4, fb);
                }
            }
            else {
                break;
            }

            e2 = 2*err;

            // determine if this step should be done on x or y axis -> increase error (difference to ideal line) and make step 
            if (e2 >= dy) {
                err += dy; 
                x1 += sx;
            }
            if (e2 <= dx) {
                err += dx; 
                y1 += sy;
            }  
            
        }
    }
}
void draw_shoot_cooldown(struct buffer fb){
    if (shoot_cool > 0){
        putB('\n', fb);
        unsigned short n = map(shoot + shoot_cool, 0, shoot_dur*(shoot_factor+1), 0, mapS*2+1);
        for (unsigned short i = 0; i < mapS*2+1; i++){
            if (i < n){
                putB('=', fb);
            }
            else {
                putB(' ', fb);
            }
        }
    }
}