#ifndef DRAW_H_
#define DRAW_H_
    
    // select single characters for display of 3d view
    // and writes to sreen buffer fb
    // check for reaching goal wall if wall is displayed
    void draw_3d(struct distance *distance, struct buffer fb);

    // places map on sreen buffer
    void draw_map(struct position player, struct buffer fb);

    // draw different menu texts 
    void draw_menu(struct buffer fb);
    
    // map integar in range to integar in other range
    int map(int x, int inMin, int inMax, int outMin, int outMax);
    // map float in range to float in other range
    float mapf(float x, float inMin, float inMax, float outMin, float outMax);
    // Pythagorean theorem a^2 + b^2 = c^2
    float pythf(float a, float b);

    // get nearest wall from player in every viewing direction (see comment in definition)
    void ray_cast(struct position player, struct distance *distance);

    // draw fps stats on screen
    void draw_fps(struct buffer fb, float time, float fps, unsigned long frame);
    // draw shooting animation
    void draw_shoot(struct buffer fb);
    // show stooting stats (under minimap)
    void draw_shoot_stats(struct buffer fb);

    #include "draw.c"


#endif // DRAW_H_
