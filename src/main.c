#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int screen[20][20];

int main(int argc, char const *argv[])
{
    int x1 = 1;
    int y1 = 1;
    int x2 = 18;
    int y2 = 10;

    int dx =  abs(x2 - x1), sx = x1<x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1<y2 ? 1 : -1;
    int err = dx+dy, e2;
    for (;;) {
        //printf("%d %d\n", x, y);
        screen[x1][y1] = 1;
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

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    } 
    return 0;
}
