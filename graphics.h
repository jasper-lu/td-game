#define PLAYER 0
#define TOWER 1
#define MONSTER 3
#define BULLET 5

#define MAX_ROWS 10
#define MAX_HEIGHT 10

#define NUM_SPRITES 4
#define MAX_SPRITE_HEIGHT 4
#define SPRITE_WIDTH 7

#define TILE_HEIGHT 4
#define TILE_WIDTH 7

#define MAP_HEIGHT 9
#define MAP_WIDTH 20

#define BORDER_WIDTH 1
#define UI_DIST TILE_HEIGHT * MAP_HEIGHT + BORDER_WIDTH*2


#define SETPOS(x, y) xt_par2(XT_SET_ROW_COL_POS, (y), (x))

struct point_t {
    int x;
    int y;
};
typedef struct point_t point_t;

struct sprite_t {
    char* graphic[MAX_SPRITE_HEIGHT];
    int height;
    int width;
    char* color;
};
typedef struct sprite_t sprite_t;

struct ui_template {
    int col;
    int row;
    char *color;
    char *string;
};
typedef struct ui_template ui_template;

//borrowed & modded from ben kurtovic
sprite_t* get_sprite(int);
void draw(point_t, sprite_t*);
point_t tile_convert(point_t* point);
void draw_ui();
