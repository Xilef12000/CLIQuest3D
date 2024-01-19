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
        short ammo;
    };
    struct level lvl;
    struct level level1 = { // current level lvl
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1},
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
        10, 10, 180, 4
    };

    struct distance
    {
        unsigned short distance;
        unsigned short walltype;
    };
    


    extern unsigned short isMenu;// = 1;
    extern unsigned short shoot;// = 0;
    extern unsigned short shoot_dur;// = 0;
    extern unsigned short shoot_cool;// = 0;
    extern const unsigned short shoot_factor;// = 4
    extern int loop;// = 1; // loop until exit

    unsigned short isMenu = 1;
    unsigned short shoot = 0;
    unsigned short shoot_dur = 0;
    unsigned short shoot_cool = 0;
    const unsigned short shoot_factor = 4;
    int loop = 1; // loop until exit

    // extern variables unchanged during game loop
    extern const unsigned short mapS;// = 10; // minimap size // must be smaller then WORLDSIZE
    extern const short fov;// = 90; //set field of view to 90 degree
    extern const short maxVDist;// = 20; //set max viewing distran
    extern const float stepXY;// = 0.5; // player step size
    extern const int stepA;// = 5;  // player rotation steps
    extern int cliX;// = 144; // default fallback windows size 
    extern int cliY;// = 48;
    extern double cliA;  // width in degrees of one character in window size

    const unsigned short mapS = 10; // minimap size // must be smaller then WORLDSIZE
    const short fov = 90; //set field of view to 90 degree
    const short maxVDist = 20; //set max viewing distran
    const float stepXY = 0.5; // player step size
    const int stepA = 5;  // player rotation steps
    int cliX = 144; // default fallback windows size 
    int cliY = 48;
    double cliA;  // width in degrees of one character in window size
    

    void draw_3d(struct distance *distance, struct buffer fb);
    void draw_map(struct position player, struct buffer fb);
    void draw_menu(struct buffer fb);
    
    int map(int x, int inMin, int inMax, int outMin, int outMax);
    void ray_cast(struct position player, struct distance *distance);

    void draw_fps(struct buffer fb, float time, float fps, unsigned long frame);
    void draw_shoot(struct buffer fb);
    void draw_shoot_stats(struct buffer fb);

    #include "draw.c"


#endif // DRAW_H_
