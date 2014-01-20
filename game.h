#include graphics.h


struct player_t {
    point_t point;
}
typedef struct player_t player_t;

struct tower_t {
    point_t point;
    int power;
    int cooldown;
    int cooldown_timer;
    //tower type
    int type;
    struct tower_t* next;
}
typedef struct tower_t tower_t;

struct enemy_t {
    point_t point;
    int speed;
    int health;
    struct enemy_t* next;
}
typedef struct enemy_t enemy_t;

struct game {
    int money;
    player_t* player;
    enemy_t* enemy_head;
    tower_t* tower_head;
}
