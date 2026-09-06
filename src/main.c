#include <stdio.h>

#include <libdragon.h>


int main(void){

    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    static surface_t *frame;

    while (1){
        while(!(frame = display_lock()));
        graphics_draw_box(frame, 20, 20, 600, 400, graphics_make_color(230, 250, 240, 255));
        display_show(frame);
    }
}