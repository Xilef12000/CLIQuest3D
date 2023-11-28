#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/time.h>

const int world[20][20] = {
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

int distance[90] = {}; // max viewing distance
float stepXY = 0.5; // player step size
int stepA = 5;  // player rotation steps
int cliX = 144; // default fallback windows size
int cliY = 48;
int map(int x, int inMin, int inMax, int outMin, int outMax) {
    // mapping function of one int in range to int in other range
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
int main(int argc, char const *argv[]) {   
    // get window size in characters
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    cliY = w.ws_row - 4;
    cliX = w.ws_col - 4;
    // variables for time stats
    struct timeval tNow, tLast;
    gettimeofday(&tLast, NULL);
    unsigned long tTaken, frame = 0;
    int key; // buffer for pressed key
    float pX = 9; // player position X
    float pY = 9; // player position Y
    int pA = 0; // player rotation in degree (view direction - 180)
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
                    pNX -= sin(pRad)*stepXY;
                    pNY -= cos(pRad)*stepXY;
                    break;
                case 'a':
                    pA+=stepA;
                    break;
                case 's':
                    pNX += sin(pRad)*stepXY;
                    pNY += cos(pRad)*stepXY;
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
        for (int a = pA; a < pA + cliX; a++) {
            float i = 0; // line step counter
            float x1 = pX; // point one = player position
            float y1 = pY;
            float srad = a*360/(double)cliX*M_PI/180; // calculate rotation/direction of line 
            float y2 = 9.5+(sin(srad)*20); // calculate point two
            float x2 = 9.5+(cos(srad)*20);

            float dx =  fabs(x2 - x1); // delta between x1 and x2
            float sx = x1<x2 ? 1 : -1; // direction of x delta -> x step
            float dy = -fabs(y2 - y1); // delta between y1 and y2
            float sy = y1<y2 ? 1 : -1; // direction of y delta -> y step
            float err = dx+dy, e2;
            while (1) {
                // if current step position in wall
                if (world[(int)x1][(int)y1] == 1) {
                    distance[a-pA] = i; // safe distance to wall (number of necessary steps)
                    break; // exit to next view line
                }
                i++; // next step
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
                if (cliY/2-(cliY-map(distance[j],0,20,0,cliY))/2 <= i) { // if pixel is not ceiling -> wall or floor
                    if (cliY/2+(cliY-map(distance[j],0,20,0,cliY))/2 >= i) { // if pixel is not floor -> wall
                        // draw gray shade depending on distance of wall to player
                        if (distance[j] < 5){
                            fputs("\u2588", stdout);
                        }
                        else if (distance[j] < 10){
                            fputs("\u2593", stdout);
                        }
                        else if (distance[j] < 15){
                            fputs("\u2592", stdout);
                        }
                        else {
                            fputs("\u2591", stdout);
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
