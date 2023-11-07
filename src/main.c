#include <stdio.h>
int world[4][5] = {{1, 1, 1, 1, 1},
                {1, 1, 0, 0, 1},
                {1, 0, 0, 1, 1},
                {1, 0, 6, 0, 1}};

int player[2] = {3, 2};

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", world[i][j]);
        }
        printf("\n");
    }

    printf("%d  %d \n", player[0], player[1]);
    printf("%d \n", world[player[0]][player[1]]);
    return 0;
}