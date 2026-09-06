#include <stdlib.h>
#include <libdragon.h>


sprite_t *createSprite(int sprite_id, const char *sprite_path)
{
    char path[64];

    if (sprite_path){
        strncpy(path, sprite_path, sizeof(path) - 1);
        path[sizeof(path) - 1] = '\0';
    }
    else {
        sprintf(path, "/sprites/sprite_%d", sprite_id);
    }

    int f = dfs_open(path);
    if (f < 0) return NULL;

    sprite_t *sprite = malloc(dfs_size(f));
    dfs_read(sprite, 1, dfs_size(f), f);
    dfs_close(f);

    return sprite;
}

void freeSprite(sprite_t *sprite)
{
    free(sprite);
    sprite = NULL;
}


int frame = 0;

int main(void){

    surface_t *disp;
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    dfs_init(DFS_DEFAULT_LOCATION);

    sprite_t *dude = createSprite(0, NULL);
    
    while(1)
    {
        while(!(disp = display_try_get()));
        graphics_fill_screen(disp, graphics_make_color(255, 255, 255, 255));
        display_show(disp);
        freeSprite(dude);
    }
    
}