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
    
    int map(int x, int inMin, int inMax, int outMin, int outMax);
    void ray_cast(struct position player, struct distance *distance);

    void draw_fps(struct buffer fb, float time, float fps, unsigned long frame);
    void draw_shoot(struct buffer fb);
    void draw_shoot_stats(struct buffer fb);

    #include "draw.c"


#endif // DRAW_H_
