#include <stdlib.h>
#include <libdragon.h>

#define NUM_STATES 5
#define NUM_INPUTS 5


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


typedef enum { STATE_IDLE, STATE_LEFT, STATE_UP, STATE_RIGHT, STATE_DOWN } State;
typedef enum { INPUT_NONE, INPUT_LEFT, INPUT_UP, INPUT_RIGHT, INPUT_DOWN } Input;

typedef struct {
    State next_state;
    const char *sprite_path;
} Transition;

Transition transition_table[NUM_STATES][NUM_INPUTS] = {
    [STATE_IDLE][INPUT_LEFT] =  { STATE_LEFT,   "/sprites/spritesheet1" },
    [STATE_IDLE][INPUT_UP] =    { STATE_UP,     "/sprites/spritesheet2" },
    [STATE_IDLE][INPUT_RIGHT] = { STATE_RIGHT,  "/sprites/spritesheet3" },
    [STATE_IDLE][INPUT_DOWN] =  { STATE_DOWN,   "/sprites/spritesheet4" },

    [STATE_LEFT][INPUT_LEFT]   = { STATE_LEFT,  NULL },
    [STATE_UP][INPUT_UP]       = { STATE_UP,    NULL },
    [STATE_RIGHT][INPUT_RIGHT] = { STATE_RIGHT, NULL },
    [STATE_DOWN][INPUT_DOWN]   = { STATE_DOWN,  NULL }
};


int main(void){

    surface_t *disp;
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    dfs_init(DFS_DEFAULT_LOCATION);
    joypad_init();

    State current_state = STATE_IDLE;
    sprite_t *dude = createSprite(0, "/sprites/spritesheet0");

    float x = 320, y =240;
    const float speed = 2.0f;
    
    int frame = 0;
    while(1)
    {
        joypad_poll();
        joypad_buttons_t held = joypad_get_buttons_held(JOYPAD_PORT_1);

        Input pressed = INPUT_NONE;
        if (held.d_left) pressed = INPUT_LEFT;
        if (held.d_up) pressed = INPUT_UP;
        if (held.d_right) pressed = INPUT_RIGHT;
        if (held.d_down) pressed = INPUT_DOWN;

        if (pressed != INPUT_NONE){
            Transition t = transition_table[current_state][pressed];
            if (t.sprite_path && t.next_state != current_state){
                freeSprite(dude);
                dude = createSprite(0, t.sprite_path);
                current_state = t.next_state;
            }

            switch (pressed){
                case INPUT_LEFT: x -= speed; break;
                case INPUT_UP: y -= speed; break;
                case INPUT_RIGHT: x += speed; break;
                case INPUT_DOWN: y += speed; break;
                default: break;
            }
        }

        else if (current_state != STATE_IDLE){
                freeSprite(dude);
                dude = createSprite(0, "/sprites/spritesheet0");
                current_state = STATE_IDLE;
        }




        while(!(disp = display_try_get()));
        graphics_fill_screen(disp, graphics_make_color(255, 255, 255, 255));
        graphics_draw_sprite_trans_stride(
            disp, 
            (int)x, 
            (int)y, 
            dude,
            (frame>>2)%16
        );
        display_show(disp);

        frame++;
    }
}