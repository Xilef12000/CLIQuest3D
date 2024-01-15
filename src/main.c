#include "quest.h"

int main(int argc, char const *argv[]) { 

    // get window size in characters
    getCliDim(&cliX, &cliY);

    struct buffer fb = init_buffer(&cliX, &cliY);
    
    cliY -= 4;
    cliX -= 4;
    cliA = fov / (double) cliX;
    
    start_fps();

    // setup array for distance to wall for each vertical display line
    //unsigned short distance[cliX][2];
    struct distance *distance;
    distance = malloc(cliX*sizeof(struct distance));
     
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
            if (shoot > 0){
                draw_shoot(fb);
                shoot--;
            } 
            draw_map(player_loc, fb);

            calc_fps(fb);
        }

        else draw_menu(fb);

        displayB(fb, &codes[0], UNILEN); // write buffer to cli
    }
    return 0; 
}






