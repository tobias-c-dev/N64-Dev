#include <stdio.h>

#include <libdragon.h>





int main(void)
{
    console_init();
    console_set_render_mode(RENDER_MANUAL);

    for (int i=0; i < 21; i++){
        console_clear();
        printf("%i\n", i);
        console_render();
        wait_ms(1000);
    }
    console_clear();
    console_close();

    while(1) {}
}