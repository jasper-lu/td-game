//includes graphics as well, in astar. Maybe i need to link better hm
#include "astar.h"
#include <time.h>
#define MILLI 1000
#define NANO 1000000000

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
    long move_timer;
    long last_moved;
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

//prototypes
void spawn_player(game_t* game);

void draw_towers(game_t* game);
tower_t* spawn_tower(game_t* game, int type);

enemy_t* spawn_enemy(game_t* game, int health, int speed);
void init_em(enemy_manager_t** p_em, int timer);
void execute_em(game_t* game);

game_t* init_game();
