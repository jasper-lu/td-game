#include "graphics.h"
#include "xterm_control.h"
#include <string.h>
#include <stdio.h>

static sprite_t sprite_table[NUM_SPRITES] = {{{0}}};
static int sprite_init = 0;
static ui_template UI[] = {
    {0,UI_DIST,XT_CH_GREEN,"____________________________________________________________________________________________________________________________________________"},
    {0,UI_DIST+1,XT_CH_GREEN,"        1|        2|        3|        4|        5|        6|        7|        8|        9|"},
    {0,UI_DIST+2,XT_CH_GREEN,"         |         |         |         |         |         |         |         |         |"},
    {0,UI_DIST+3,XT_CH_GREEN," |       |         |         |         |         |         |         |         |         |"},
    {0,UI_DIST+4,XT_CH_GREEN," |       |         |         |         |         |         |         |         |         |"},
    {0,UI_DIST+5,XT_CH_GREEN,"100G_____|_________|_________|_________|_________|_________|_________|_________|_________|__________________________________________________"},
    //for the entrance/exit
    {-1,BORDER_WIDTH - 2 + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN,"─"},
    {-1,BORDER_WIDTH - 1 + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN," "},
    {-1,BORDER_WIDTH + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN," "},
    {-1,BORDER_WIDTH + 1 + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN," "},
    {-1,BORDER_WIDTH + 2 + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN,"_"},
    {MAP_WIDTH*TILE_WIDTH,BORDER_WIDTH - 2 + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN,"─"},
    {MAP_WIDTH*TILE_WIDTH,BORDER_WIDTH - 1 + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN," "},
    {MAP_WIDTH*TILE_WIDTH,BORDER_WIDTH + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN," "},
    {MAP_WIDTH*TILE_WIDTH,BORDER_WIDTH + 1 + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN," "},
    {MAP_WIDTH*TILE_WIDTH,BORDER_WIDTH + 2 + MAP_HEIGHT*TILE_HEIGHT / 2, XT_CH_GREEN,"_"},
    {MAP_WIDTH*TILE_WIDTH - 51, UI_DIST+2,XT_CH_GREEN, "| Level:"},
    {MAP_WIDTH*TILE_WIDTH - 51, UI_DIST+3,XT_CH_GREEN, "| Next wave:"},
    {MAP_WIDTH*TILE_WIDTH - 51, UI_DIST+4,XT_CH_GREEN, "| Lives:"},
    {MAP_WIDTH*TILE_WIDTH - 51, UI_DIST+5,XT_CH_GREEN, "| Gold:"},
};
static int ui_size = 20;

void draw_ui() {
    int i;
    //a lot of the stuff in the following code secition may not make sense. They were used to positino the stuff, but there are a lot of 1 borders, etc. idk... it's still readable [the code] though, at least
    //lol hard coded borders
    for (i = 2; i != 44; ++i) {
        SETPOS(1,i);
        putchar('|');
        SETPOS(TILE_WIDTH * MAP_WIDTH + BORDER_WIDTH * 2,i);
        putchar('|');
    }
    for(i = 2; i != MAP_WIDTH * TILE_WIDTH + BORDER_WIDTH * 2; ++i) {
        SETPOS(i,1);
        putchar('_');
    }
    for(i = 0; i != ui_size; ++i) {
        SETPOS(UI[i].col + BORDER_WIDTH + 1, UI[i].row);
        printf("%s", UI[i].string);
    }
    draw((point_t){3,UI_DIST+1},get_sprite(TOWER));
    draw((point_t){23,UI_DIST+2},get_sprite(MONSTER));
    //smoe hard-coded stuff to draw the time till next wave and the lives
    
    //the timer seconds thing is in spawn wave check to save time
}

static void init_sprites(void) {
    sprite_table[PLAYER] = (sprite_t) {
        {
            "╔═---═╗",
            "¦ ┌ ┐ ¦",
            "¦ └ ┘ ¦",
            "╚═---═╝"
        },4,15,XT_CH_BLUE
    };
    sprite_table[TOWER] = (sprite_t) {
        {
            "_______",
            "|\\___/|",
            "| |A| |",
            "|/___\\|"
                /*
            "┌\\───/┐",
            "| |Ã| |",
            "|/ ¯ \\|",
            "└─────┘"
            */
        },4,7,XT_CH_WHITE
    };
    sprite_table[MONSTER] = (sprite_t) {
        {
            " ═╗_╔═ ", 
            "╚═|U|═╝",
            "╔═|O|═╗",
            " ═╝ ╚═ "
        }, 4, 15, XT_CH_RED
    };
    sprite_table[BULLET] = (sprite_t) {
        {
            "o"
        }, 1, 1, XT_CH_BLUE
    };
}


sprite_t* get_sprite(int name) {
    if(!sprite_init)
        init_sprites();
    return &sprite_table[name];
}

//converts from tile coord to pixel coord
point_t tile_convert(point_t* point) {
    return (point_t){point->x * TILE_WIDTH + 1 + BORDER_WIDTH, point->y * TILE_HEIGHT + 1 + BORDER_WIDTH};
}

void draw(point_t point, sprite_t* sprite) {
    int r, c;
    for(r = 0; r!= sprite->height; r++){
        SETPOS(point.x,point.y + r);
        for(c = 0; c!= sprite->width; ++c){
            putchar(sprite->graphic[r][c]);
        }
    }
    xt_par0(XT_CH_NORMAL); 
}

