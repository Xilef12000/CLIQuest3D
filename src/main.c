#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "crossplatform.h"
#include <sys/time.h>
#include "framebuffer.h"
#include "menu.h"
#include <math.h>

int map(int x, int inMin, int inMax, int outMin, int outMax);

#define WORLDSIZE 20
const int world[WORLDSIZE][WORLDSIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
}; // birds perspective of world (world needs a boarder!)

const float spX = 10; // spawn coordinates and rotation
const float spY = 10;
const int spA = 180;
const short fov = 90; //set field of view to 90 degree
const short maxVDist = 20; //set max viewing distran
const float stepXY = 0.5; // player step size
const int stepA = 5;  // player rotation steps
int cliX = 144; // default fallback windows size 
int cliY = 48;
//char keystr[30];
//char *keyptr;

int main(int argc, char const *argv[]) { 
    // menu
    unsigned short isMenu = 1;
    // output character dictionary  
    #define CODESLEN UNILEN
    struct dict codes[CODESLEN];
    setCodes(&codes[0], CODESLEN);
    // init buffer
    struct buffer fb;
    fb.sY = malloc(sizeof(unsigned short));
    fb.sX = malloc(sizeof(unsigned short));
    // get window size in characters
    if (getCliDim(fb)){
        cliY = (*fb.sY) - 4;
        cliX = (*fb.sX) - 4;
    }
    double cliA = fov / (double) cliX;
    // clear buffer
    fb.bP = malloc(sizeof(unsigned short)*(*fb.sX)*(*fb.sY));
    fb.cur = malloc(sizeof(fb.cur));
    (*fb.cur) = 0; // avoid undefined values
    for (int i = 0; i < (*fb.sX)*(*fb.sY); i++){
        fb.bP[i] = 32;
    }
    // setup array for distance to wall for each vertical display line
    unsigned short *distance;
    distance = malloc(sizeof(unsigned short)*cliX);
    // variables for time stats
    struct timeval tNow, tLast;
    gettimeofday(&tLast, NULL);
    unsigned long tTaken, frame = 0;
    int key; // buffer for pressed key
    float pX = spX; // player position X
    float pY = spY; // player position Y
    int pA = spA; // player rotation in degree (180 = north)
    float pNX, pNY, pRad; // new theoretical player position x y and rotation in radians
    unsigned short mapS = 10; // minimap size // must be smaller then WORLDSIZE
    printf("\e[1;1H\e[2J"); // cursor to top left of page and clear page
    int loop = 1; // loop until exit
    while(loop) {
        //int inBuffer = getKeysInBuffer(keyptr); // how many characters in input buffer
        while(getKeysInBuffer()) //inBuffer > 0
        {
        //for (int b = 0; b < inBuffer; b++) {
            //inBuffer--; // for every character in input buffer
            key = getKey(); // get character
            if (!isMenu){
            pRad = pA*M_PI/180; // degree to radians
            pNX = pX; // theoretical new position = current position
            pNY = pY;
            switch (key) {
                // rotate or walk according to key press, exit if '.'
                case 'w':
                    pNX += sin(pRad)*stepXY;
                    pNY += cos(pRad)*stepXY;
                    break;
                case 'a':
                    pA+=stepA;
                    break;
                case 's':
                    pNX -= sin(pRad)*stepXY;
                    pNY -= cos(pRad)*stepXY;
                    break;
                case 'd':
                    pA-=stepA;
                    break;
                case  '.':
                    isMenu = 1;
                    break;
            }
            }
            else {
                switch (key) {
                case  '.':
                    loop = 0;
                    break;
                case ' ':
                    isMenu = 0;
                    break;
                }
            }
            // check if theoretical new position is not in wall -> write it to current position
            if(world[(int)(pY)][(int)pNX] == 0) {
                pX = pNX;
            }
            if(world[(int)(pNY)][(int)pX] == 0) {
                pY = pNY;
            }
        }
        if (!isMenu){
        // ray casting:
        // draw lines from player in every direction in view
        // lines can only be draws between between to points
        // point one: player, and point two a pointer outside of world so it can never be reached
        // the line is drawn in small steps from the first to the second point
        for (int i = 0; i < cliX; i++) {
            float l = 0; // line step counter
            float x1 = pY; // point one = player position
            float y1 = pX;
            // line degree in radiens (looking direction - half pov + line offset)
            float srad = (((pA - (double) fov / 2) + (i * cliA)) * M_PI) / 180;
            float y2 = y1+(sin(srad)*WORLDSIZE+1); // calculate point two
            float x2 = x1+(cos(srad)*WORLDSIZE+1);

            float dx =  fabs(x2 - x1); // delta between x1 and x2
            float sx = x1<x2 ? 0.1 : -0.1; // direction of x delta -> x step
            float dy = -fabs(y2 - y1); // delta between y1 and y2
            float sy = y1<y2 ? 0.1 : -0.1; // direction of y delta -> y step
            float err = dx+dy, e2;
            while (1) {
                // if current step position in wall
                if (world[(int)x1][(int)y1] == 1) {
                    distance[i] = l/10; // safe distance to wall (number of necessary steps)
                    break; // exit to next view line
                }
                l++; // next step
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
        }
        fprintB(fb, "X:%6.3f/Y:%6.3f/% 4d° \r\n", pX, pY, pA); // print player coordinates and rotation
        setBCur(0, 1, fb);
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
        // draw map
        setBCur(0, 1, fb); //reset cursor to top left corner
        short mY1 = pY-(float)mapS/2;
        mY1 = mY1 > 0 ? mY1 : 0;
        short mY2 = mY1 == 0 ? mY1+mapS : pY+(float)mapS/2;
        mY2 = mY2 < WORLDSIZE ? mY2 : WORLDSIZE;
        mY1 = mY2 != WORLDSIZE ? mY1 : mY2-mapS;
        short mX1 = pX-(float)mapS/2;
        mX1 = mX1 > 0 ? mX1 : 0;
        short mX2 = mX1 == 0 ? mX1+mapS : pX+(float)mapS/2;
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
                if (world[i][j] == 1) {
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
        setBCur((int)pX*2-mX1*2, pY-mY1+2, fb);
        switch (map(((((int)(pA-180+22.5) % 360)+360) % 360), 0, 360, 0, 8)) {
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
        

        // calculate and output time stats
        gettimeofday(&tNow, NULL);
        tTaken = (tNow.tv_sec - tLast.tv_sec) * 1000000 + tNow.tv_usec - tLast.tv_usec;
        setBCur(0, cliY+2, fb);
        fprintB(fb, "time: %10.4f ms; fps: %10.0f; frame: %10.0lu; \n", (float) tTaken / 1000, (float) 1.0/tTaken*1000000, frame); 
        tLast = tNow;
        frame++;
        }
        else {
            clearB(fb);
            setBCur(0, 3, fb);
            for (int i = 0; i < 8; i++) {
                printB((char*)logo[i], fb);
                putB('\n', fb);
            }
            printB("\n\n Press SPACE to start game", fb);
            printB("\n\n or . to exit game.", fb);
            printB("\n\n\n\n\n\n Credits:\n", fb);
            printB("\n Niklas Bachmann      https://github.com/alavanou", fb);
            printB("\n Manuel Koenig        https://github.com/Xilef12000", fb);
            printB("\n\n\n\n This Project on Github:\n", fb);
            printB("\n https://github.com/Xilef12000/CLIQuest3D", fb);
        }

        displayB(fb, &codes[0], CODESLEN); // write buffer to cli
    }
    return 0;
}

int map(int x, int inMin, int inMax, int outMin, int outMax) {
    // mapping function of one int in range to int in other range
    int n = (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    if (n > outMax) n = outMax;
    if (n < outMin) n = outMin;
    return n;
}