#include "graphics.h"
#include "xterm_control.h"

static sprite_t sprite_table[NUM_SPRITES] = {{{0}}};
static int sprite_init = 0;

static void init_sprites(void) {
    sprite_table[PLAYER] = (sprite_t) {
        {
            "-------",
            "| 0  0|",
            "|  __ |",
            "-------"
        },4,7,XT_CH_BLUE
    };
    sprite_table[TOWER] = (sprite_t) {
        {
            "_______",
            "|\\___/|",
            "| |A| |",
            "|/___\\|"
        },4,7,XT_CH_WHITE
    };
}

sprite_t* get_sprite(int name) {
    if(!sprite_init)
        init_sprites();
    return &sprite_table[name];
}

void draw(point_t* point, sprite_t* sprite) {
    int t_x = point->x;
    int t_y = point->y;
    int r, c;
    for(r = 0; r!= sprite->height; r++){
        SETPOS(t_x, t_y + r);
        for(c = 0; c!= sprite->width; ++c){
            putchar(sprite->graphic[r][c]);
        }
    }
}
