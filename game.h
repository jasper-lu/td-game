#include graphics.h

//prototypes
static_void spawn_player(*game_t);
static_void spawn_tower(*game_t, int x, int y, int type);
static_void spawn_enemy(*game_t, int health, int speed);

struct player_t {
    point_t point;
}

struct tower_t {
    point_t point;
    int power;
    int reload;
    //tower type
    int type;
}

struct enemy_t {
    point_t point;
    int speed;
    int health;
}
