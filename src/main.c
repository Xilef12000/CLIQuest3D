#include <math.h>
#include <stdio.h>

int screen[20][20];

int main(int argc, char const *argv[])
{
    int x1 = 1;
    int y1 = 1;
    int x2 = 18;
    int y2 = 10;

    for (int x = x1; x<= x2; x++){
    int run = x - x1;
    double m = (double)(y2 -y1)/(x2-x1);
    int y = m*run + y1;
    
    //printf("%d %d\n", x, y);
    screen[x][y] = 1;
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    } 
	return 0;
}
