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
    unsigned short distance[cliX];
     
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




void ray_cast(struct position player_loc, unsigned short *distance){
    // ray casting:
    // draw lines from player_loc in every direction in view
    // lines can only be drawn between between to points
    // point one: player_loc, and point two a pointer outside of world so it can never be reached
    // the line is drawn in small steps from the first to the second point
    for (int i = 0; i < cliX; i++) {
        float l = 0; // line step counter
        float x1 = player_loc.pY; // point one = player_loc position
        float y1 = player_loc.pX;
        // line degree in radiens (looking direction - half pov + line offset)
        float srad = (((player_loc.pA - (double) fov / 2) + (i * cliA)) * M_PI) / 180;
        float y2 = y1+(sin(srad)*WORLDSIZE+1); // calculate point two
        float x2 = x1+(cos(srad)*WORLDSIZE+1);

        float dx =  fabs(x2 - x1); // delta between x1 and x2
        float sx = x1<x2 ? 0.1 : -0.1; // direction of x delta -> x step
        float dy = -fabs(y2 - y1); // delta between y1 and y2
        float sy = y1<y2 ? 0.1 : -0.1; // direction of y delta -> y step
        float err = dx+dy, e2;
        while (1) {
            // if current step position in wall
            if (lvl.world[(int)x1][(int)y1] == 1) {
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
}


