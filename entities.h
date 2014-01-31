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
    int radius;
    int b_speed;
    long cooldown;
    long cooldown_timer;
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
    int spawn_numb;
    //time to next wave
    long wave_timer;
    //time until wave
    long wave_load;
    //will be calced to find the time to next spawn
    //time to next spawn
    int speed;
    //last moved
    long last_moved;
//    health of the mobs of the current wave
    int health;
    enemy_t* enemy_head;
};
typedef struct enemy_manager_t enemy_manager_t;

struct bullet_t {
    point_t point;
    int dmg;
    long move_timer;
    long last_moved;
    enemy_t* target;
    struct bullet_t* next;
};
typedef struct bullet_t bullet_t;

struct game_t {
    int money;
    int lives;
    player_t player;
    enemy_manager_t* e_manager;
    tower_t* tower_head;
    bullet_t* bullet_head;
    char** map;
};
typedef struct game_t game_t;
//prototypes
void spawn_player(game_t* game);

void draw_towers(game_t* game);
tower_t* spawn_tower(game_t* game, int type);

enemy_t* spawn_enemy(enemy_manager_t* em, int health, int speed);
void init_em(enemy_manager_t** p_em, int timer);
void execute_em(game_t* game);

bullet_t* spawn_bullet(game_t* game, enemy_t* target, point_t point, int damage, int speed);
void execute_bt(game_t* game);

void set_spawn_wave(int speed, int health, int spawn_numb, enemy_manager_t* em);
game_t* init_game();
