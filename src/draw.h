#ifndef DRAW_H_
#define DRAW_H_

    #include "framebuffer.h"
    #include "menu.h"


    struct position{
        float pX; // player position X
        float pY; // player position Y
        int pA; // player rotation in degree (180 = north)
    };

    #define WORLDSIZE 20
    struct level {
        int world[WORLDSIZE][WORLDSIZE]; // birds perspective of world (world needs a boarder!)
        struct position spawn;
    };

    struct level lvl = { // current level lvl
        {
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
        }, 
        10, 10, 180
    };


    void draw_3d(unsigned short *distance, struct buffer fb);
    void draw_map(struct position player, struct buffer fb);
    void draw_menu(struct buffer fb);
    
    int map(int x, int inMin, int inMax, int outMin, int outMax);
    struct position kb_control(struct position player);
    void ray_cast(struct position player, unsigned short *distance);


    // menu
    extern unsigned short isMenu;// = 1;
    extern int loop;// = 1; // loop until exit

    extern const unsigned short mapS;// = 10; // minimap size // must be smaller then WORLDSIZE
    extern const short fov;// = 90; //set field of view to 90 degree
    extern const short maxVDist;// = 20; //set max viewing distran
    extern const float stepXY;// = 0.5; // player step size
    extern const int stepA;// = 5;  // player rotation steps
    extern int cliX;// = 144; // default fallback windows size 
    extern int cliY;// = 48;
    extern double cliA;  // width in degrees of one character in window size

    unsigned short isMenu = 1;
    int loop = 1; // loop until exit

    const unsigned short mapS = 10; // minimap size // must be smaller then WORLDSIZE
    const short fov = 90; //set field of view to 90 degree
    const short maxVDist = 20; //set max viewing distran
    const float stepXY = 0.5; // player step size
    const int stepA = 5;  // player rotation steps
    int cliX = 144; // default fallback windows size 
    int cliY = 48;
    double cliA;  // width in degrees of one character in window size
        
    #include "draw.c"


#endif // DRAW_H_
