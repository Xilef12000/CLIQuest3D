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

    int dx = x2 - x1;
    int dy = y2 - y1;
    int D = 2*dy - dx;
    int y = y1;
    for (int x = x1; x < x2; x++){
        //printf("%d %d\n", x, y);
        screen[x][y] = 1;

        if (D > 0){
            y++;
            D -= 2*dx;
        }
        D += 2*dy;
    }
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    } 
	return 0;
}
