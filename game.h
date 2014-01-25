//includes graphics as well, in astar. Maybe i need to link better hm
#include "astar.h"

struct player_t {
    point_t point;
};
typedef struct player_t player_t;

struct tower_t {
    point_t point;
    int power;
    int cooldown;
    int cooldown_timer;
    //tower type
    int type;
    struct tower_t* next;
};
typedef struct tower_t tower_t;

struct enemy_t {
    point_t point;
    point_t dest;
    //per second
    int speed;
    int move_timer;
    int health;
    struct enemy_t* next;
};
typedef struct enemy_t enemy_t;

struct enemy_manager_t {
    int level;
    //time to next wave
    int wave_load;
    //time until wave
    int wave_timer;
    enemy_t* enemy_head;
};
typedef struct enemy_manager_t enemy_manager_t;

struct game_t {
    int money;
    int lives;
    player_t player;
    enemy_manager_t* e_manager;
    tower_t* tower_head;
    char** map;
};
typedef struct game_t game_t;
