#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>

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
};
int screen[20][20];
int distance[90] = {};
float stepXY = 0.5;
int stepA = 5;
int cliX = 144;
int cliY = 48;
const char grey[66] = " .'`^,:;Il!i><~+_-?][}{1)(|tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8B@$";
int map(int x, int inMin, int inMax, int outMin, int outMax) {
  return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
int main(int argc, char const *argv[])
{   
    clock_t lastt = clock();
    int key;
    float pX = 9;
    float pY = 9;
    int pA = 0;
    float pNX, pNY, pRad;
    system ("/bin/stty raw");
    system ("/bin/stty -echo");
    system ("tput civis");
    printf("\e[1;1H\e[2J");
    int loop = 1;
    while(loop) {
        int inBuffer;
        ioctl(0, FIONREAD, &inBuffer);
        while (inBuffer > 0){
            inBuffer--;
            key=getchar();
            pRad = pA*M_PI/180;
            pNX = pX;
            pNY = pY;
            switch (key) {
            case 'w':
                pNX -= sin(pRad)*stepXY;
                pNY -= cos(pRad)*stepXY;
                break;
            case 'a':
                pNX -= cos(pRad)*stepXY;
                pNY -= sin(pRad)*stepXY;
                break;
            case 's':
                pNX += sin(pRad)*stepXY;
                pNY += cos(pRad)*stepXY;
                break;
            case 'd':
                pNX += cos(pRad)*stepXY;
                pNY += sin(pRad)*stepXY;
                break;
            case 'q':
                pA+=stepA;
                break;
            case 'e':
                pA-=stepA;
                break;
            case  '.':
                loop = 0;
                break;
            }
            if(world[(int)(pNX)][(int)pY] == 0){
                pX = pNX;
            }
            if(world[(int)(pX)][(int)pNY] == 0){
                pY = pNY;
            }
        }

        for (int i = 0; i < 20; i++){
            for (int n = 0; n < 20; n++){
                screen[i][n] = 0;
            }
        }
        for (int a = pA; a < pA + cliX; a++){
            float i = 0;
            float x1 = pX;
            float y1 = pY;
            float srad = a*360/(double)cliX*M_PI/180;
            float y2 = 9.5+( sin(srad)*20);
            float x2 = 9.5+( cos(srad)*20);

            float dx =  fabs(x2 - x1), sx = x1<x2 ? 1 : -1;
            float dy = -fabs(y2 - y1), sy = y1<y2 ? 1 : -1;
            float err = dx+dy, e2;
            for (;;) {
                //printf("%d %d\r\n", x, y);
                if (world[(int)x1][(int)y1] == 1){
                    screen[(int)x1][(int)y1] = 66;
                    distance[a-pA] = i;
                    break;
                }
                if (screen[(int)x1][(int)y1] < i){
                    screen[(int)x1][(int)y1] = i;  
                }
                i++;
                e2 = 2*err;

                if (e2 >= dy) 
                {
                    if (x1 == x2) 
                        break;
                    err += dy; 
                    x1 += sx;
                }

                else if (e2 <= dx) 
                {
                    if (y1 == y2) 
                        break;
                    err += dx; 
                    y1 += sy;
                }   
            }
        }

        //printf("\e[1;1H\e[2J");
        printf("\e[1;1H");
        printf("X:%6.3f/Y:%6.3f/% 4d° \r\n", pX, pY, pA);
        /*
        screen[(int)pX][(int)pY] = 65;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                //printf("%d ", screen[i][j]);
                printf("%c ", grey[screen[i][j]]);
            }
            fputs("\r\n", stdout);
        } 
        fputs("\r\n", stdout);
        
        for (int j = cliX-1; j >= 0; j--) {
            printf("%c", grey[65 - distance[j]]);
        }
        */
        fputs("\r\n", stdout);
        for (int i = 0; i < cliY; i++) {
            for (int j = cliX-1; j >= 0; j--) {
                if (cliY/2-(cliY-map(distance[j],0,20,0,cliY))/2 <= i && cliY/2+(cliY-map(distance[j],0,20,0,cliY))/2 >= i){
                    fputs("#", stdout);
                }
                else {
                    fputs(" ", stdout);
                }
            }
            fputs("\r\n", stdout);
        } 
        
        time_t time = clock() - lastt;
        printf("time: %.3f ms; fps: %.0f \r\n", (((double) time) / CLOCKS_PER_SEC)*1000, 1.0/(((double) time) / CLOCKS_PER_SEC));
        lastt = clock();
    }
    system ("/bin/stty sane");
    system ("tput cnorm");
    return 0;
}
