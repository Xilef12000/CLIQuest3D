#include "quest.h"

int main(int argc, char const *argv[]) { 

    // get window size in characters
    getCliDim(&cliX, &cliY);

    struct buffer fb = init_buffer(&cliX, &cliY);
    
    cliY -= 4;
    cliX -= 4;
    cliA = fov / (double) cliX;

    
    // variables for time stats
    struct timeval tNow, tLast;
    unsigned long tTaken, frame = 0;
    gettimeofday(&tLast, NULL);

    // setup array for distance to wall for each vertical display line
    unsigned short distance[cliX][2];
     
    // initialize player_loc position
    struct position player_loc;
    player_loc = lvl.spawn;

    initOS();
    
    while(loop) {

        while(getKeysInBuffer()) player_loc = kb_control(player_loc); // inBuffer > 0
        
        if (!isMenu){
            ray_cast(player_loc, distance);

            // print player_loc coordinates and rotation
            fprintB(fb, "X:%6.3f/Y:%6.3f/% 4d° \r\n", player_loc.pX, player_loc.pY, player_loc.pA); 
            setBCur(0, 1, fb);

            draw_3d(distance, fb);
            draw_map(player_loc, fb);

            // calculate and output time stats
            gettimeofday(&tNow, NULL);
            tTaken = (tNow.tv_sec - tLast.tv_sec) * 1000000 + tNow.tv_usec - tLast.tv_usec;
            setBCur(0, cliY+2, fb);
            fprintB(fb, "time: %10.4f ms; fps: %10.0f; frame: %10.0lu; \n", (float) tTaken / 1000, (float) 1.0/tTaken*1000000, frame); 
            tLast = tNow;
            frame++;
        }

        else draw_menu(fb);

        displayB(fb, &codes[0], UNILEN); // write buffer to cli
    }
    return 0; 
}






