#include "draw.h"

int map(int x, int inMin, int inMax, int outMin, int outMax) {
    // mapping function of one int in range to int in other range
    int n = (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    if (n > outMax) n = outMax;
    if (n < outMin) n = outMin;
    return n;
}

void draw_3d(unsigned short *distance, struct buffer fb)
{
    for (int i = 0; i < cliY; i++) { //for every horizontal line of output image
        for (int j = cliX-1; j >= 0; j--) { // for every pixel in horizontal line
            if (cliY/2-(cliY-map(distance[j],0,maxVDist,0,cliY))/2 <= i) { // if pixel is not ceiling -> wall or floor
                if (cliY/2+(cliY-map(distance[j],0,maxVDist,0,cliY))/2 >= i) { // if pixel is not floor -> wall
                    // draw gray shade depending on distance of wall to player
                    if (distance[j] < maxVDist*0.25){
                        putB(11000, fb);
                    }
                    else if (distance[j] < maxVDist*0.5){
                        putB(11001, fb);
                    }
                    else if (distance[j] < maxVDist*0.75){
                        putB(11002, fb);
                    }
                    else if (distance[j] < maxVDist){
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
