#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/time.h>

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
int distance[90] = {}; // viewing distance
const float stepXY = 0.5; // player step size
const int stepA = 5;  // player rotation steps
int cliX = 144; // default fallback windows size
int cliY = 48;
int map(int x, int inMin, int inMax, int outMin, int outMax) {
    // mapping function of one int in range to int in other range
    int n = (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    if (n > outMax) n = outMax;
    if (n < outMin) n = outMin;
    return n;
}
int main(int argc, char const *argv[]) {   
    // get window size in characters
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    cliY = w.ws_row - 4;
    cliX = w.ws_col - 4;
    double cliA = fov / (double) cliX;
    // variables for time stats
    struct timeval tNow, tLast;
    gettimeofday(&tLast, NULL);
    unsigned long tTaken, frame = 0;
    int key; // buffer for pressed key
    float pX = spX; // player position X
    float pY = spY; // player position Y
    int pA = spA; // player rotation in degree (180 = north)
    float pNX, pNY, pRad; // new theoretical player position x y and rotation in radians
    // set shell flags
    system ("/bin/stty raw"); // canonical mode -> direct input/output
    system ("/bin/stty -echo"); // no echo of user input
    system ("tput civis"); // hide blinking cursor
    printf("\e[1;1H\e[2J"); // cursor to top left of page and clear page
    int loop = 1; // loop until exit
    while(loop) {
        int inBuffer;
        ioctl(0, FIONREAD, &inBuffer); // how many characters in input buffer
        while (inBuffer > 0) {
            inBuffer--; // for every character in input buffer
            key=getchar(); // get character
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
                    loop = 0;
                    break;
            }
            // check if theoretical new position is not in wall -> write it to current position
            if(world[(int)(pNX)][(int)pY] == 0) {
                pX = pNX;
            }
            if(world[(int)(pX)][(int)pNY] == 0) {
                pY = pNY;
            }
        }
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
        printf("\e[1;1H"); // cursor to top left
        printf("X:%6.3f/Y:%6.3f/% 4d° \r\n", pX, pY, pA); // print player coordinates and rotation
        fputs("\r\n", stdout);
        for (int i = 0; i < cliY; i++) { //for every horizontal line of output image
            for (int j = cliX-1; j >= 0; j--) { // for every pixel in horizontal line
                if (cliY/2-(cliY-map(distance[j],0,maxVDist,0,cliY))/2 <= i) { // if pixel is not ceiling -> wall or floor
                    if (cliY/2+(cliY-map(distance[j],0,maxVDist,0,cliY))/2 >= i) { // if pixel is not floor -> wall
                        // draw gray shade depending on distance of wall to player
                        if (distance[j] < maxVDist*0.25){
                            fputs("\u2588", stdout);
                        }
                        else if (distance[j] < maxVDist*0.5){
                            fputs("\u2593", stdout);
                        }
                        else if (distance[j] < maxVDist*0.75){
                            fputs("\u2592", stdout);
                        }
                        else if (distance[j] < maxVDist){
                            fputs("\u2591", stdout);
                        }
                        else {
                            fputs(" ", stdout);
                        }
                    }
                    else { // -> pixel is floor
                        //  draw gray shade depending on distance of floor to player
                        if (i < cliY/2/7*1){
                            fputs("\u2581", stdout);
                        }
                        else if (i < cliY/2+cliY/2/7*2){
                            fputs("\u2582", stdout);
                        }
                        else if (i < cliY/2+cliY/2/7*3){
                            fputs("\u2583", stdout);
                        }
                        else if (i < cliY/2+cliY/2/7*4){
                            fputs("\u2584", stdout);
                        }
                        else if (i < cliY/2+cliY/2/7*5){
                            fputs("\u2585", stdout);
                        }
                        else if (i < cliY/2+cliY/2/7*6){
                            fputs("\u2586", stdout);
                        }
                        else {
                            fputs("\u2587", stdout);
                        }
                    }
                }
                else { // -> pixel is ceiling
                    fputs(" ", stdout); // empty pixel
                }
            }
            fputs("\r\n", stdout); // cursor to new line after end of horizontal line 
        } 

        // calculate and output time stats
        gettimeofday(&tNow, NULL);
        tTaken = (tNow.tv_sec - tLast.tv_sec) * 1000000 + tNow.tv_usec - tLast.tv_usec;
        printf("time: %10.4f ms; fps: %10.0f; frame: %10.0lu; \n", (float) tTaken / 1000, (float) 1.0/tTaken*1000000, frame); 
        tLast = tNow;
        frame++;
    }
    system ("/bin/stty sane"); // reset shell flags to default
    system ("tput cnorm"); // show cursor in shell
    return 0;
}
