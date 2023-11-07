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

const char grey[66] = " .'`^,:;Il!i><~+_-?][}{1)(|tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8B@$";
clock_t start, end;
int main(int argc, char const *argv[])
{
    int key;
    int bw;
    int px = 9;
    int py = 9;
    int pa = 0;
    system ("/bin/stty raw");
    system ("/bin/stty -echo");
    while(1) {
        ioctl(0, FIONREAD, &bw);
        start = clock();
        if (bw > 0){
            key=getchar();
            switch (key) {
            case 'w':
                px--;
                break;
            case 'a':
                py--;
                break;
            case 's':
                px++;
                break;
            case 'd':
                py++;
                break;
            case 'q':
                pa+=15;
                break;
            case 'e':
                pa-=15;
                break;
            case  '.':
                return 0;
                break;
            }
        }
        system ("/bin/stty cooked");
        for (int i = 0; i < 20; i++){
            for (int n = 0; n < 20; n++){
                screen[i][n] = 0;
            }
        }
        for (int a = pa; a < pa + 90; a++){
            int i = 0;
            int x1 = px;
            int y1 = py;
            int y2 = 9.5+( sin(a*4*M_PI/180)*20);
            int x2 = 9.5+( cos(a*4*M_PI/180)*20);

            int dx =  abs(x2 - x1), sx = x1<x2 ? 1 : -1;
            int dy = -abs(y2 - y1), sy = y1<y2 ? 1 : -1;
            int err = dx+dy, e2;
            for (;;) {
                //printf("%d %d\n", x, y);
                if (world[x1][y1] == 1){
                    screen[x1][y1] = 66;
                    distance[a-pa] = i;
                    break;
                }
                if (screen[x1][y1] < i){
                    screen[x1][y1] = i;  
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


        printf("\e[1;1H\e[2J");

        screen[px][py] = 65;
        printf("%d, %d \n", px, py);
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                //printf("%d ", screen[i][j]);
                printf("%c ", grey[screen[i][j]]);
            }
            printf("\n");
        } 
        printf("\n");
        
        for (int j = 89; j >= 0; j--) {
            printf("%c", grey[65 - distance[j]]);
        }
        printf("\n");

        for (int i = 0; i < 20; i++) {
            for (int j = 89; j >= 0; j--) {
                if (10-(20-distance[j])/2 <= i && 10+(20-distance[j])/2 >= i){
                    printf("#");
                }
                else {
                    printf(" ");
                }
            }
            printf("\n");
        } 
        end = clock();
        printf("time: %f s \n", ((double) (end - start)) / CLOCKS_PER_SEC);

        system ("/bin/stty raw");
    }
    system ("/bin/stty cooked");
    system ("/bin/stty echo");
    return 0;
}
