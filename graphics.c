#include "graphics.h"
#include "xterm_control.h"

static sprite_t sprite_table[NUM_SPRITES] = {{{0}}};
static int sprite_init = 0;
static ui_template UI[] = {
    {0,0,XT_CH_GREEN,"________________________________________________________________________________________________________"},
    {0,1,XT_CH_GREEN," _______1|       2 |"},
    {0,2,XT_CH_GREEN," |\\___/| |"},
    {0,3,XT_CH_GREEN," | |A| | |"},
    {0,4,XT_CH_GREEN," |/___\\| |"},
    {0,5,XT_CH_GREEN,"100G_____|_________|____________________________________________________________________________________"}
};
static int ui_size = 6;

void draw_ui() {
    int i;
    for(i = 0; i != ui_size; ++i) {
        SETPOS(UI[i].col + BORDER_WIDTH + 1, UI[i].row +1 +  MAP_HEIGHT * TILE_HEIGHT);
        printf("%s", UI[i].string);
    }
}

static void init_sprites(void) {
    sprite_table[PLAYER] = (sprite_t) {
        {
            "_______",
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
        SETPOS(t_x*TILE_WIDTH + 1 + BORDER_WIDTH, t_y * TILE_HEIGHT + r + 1);
        for(c = 0; c!= sprite->width; ++c){
            putchar(sprite->graphic[r][c]);
        }
    }
}
