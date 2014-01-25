#include "entities.h"
#include <stdlib.h>

void spawn_player(game_t* game) {
    game->player = (player_t){(point_t){0,0}};
}

void draw_towers(game_t* game) {
    tower_t* temp = game->tower_head;
    while(temp) {
        draw(&temp->point, get_sprite(temp->type));
        temp = temp->next;
    }
}

tower_t* spawn_tower(game_t* game, int type) {
    tower_t* temp_tower = malloc(sizeof(tower_t));
    *temp_tower = (tower_t) {(point_t) {game->player.point.x,game->player.point.y}, 10, 30, 0, TOWER, game->tower_head};
    game->tower_head = temp_tower;
    return temp_tower;
}

enemy_t* spawn_enemy(game_t* game, int health, int speed) {
    enemy_t* temp_enemy = malloc(sizeof(enemy_t));
    //magic numers for starting point and ending point. will change eventually??
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec;
    *temp_enemy = (enemy_t) {(point_t) {0,4}, (point_t){19,4},NANO/speed,lm,health,game->e_manager->enemy_head};
    game->e_manager->enemy_head = temp_enemy;
    return temp_enemy;
}

//ben kurtovic thanks. Way to despawn without being overly complicated
enemy_t* despawn_enemy(enemy_manager_t* em, enemy_t* enemy, enemy_t* prev) {
    enemy_t* next = enemy->next;
    if (prev)
        prev->next = next;
    else
        em->enemy_head = next;
    free(enemy);
    return next;
}

void init_em(enemy_manager_t** p_em, int timer) {
    *p_em = malloc(sizeof(enemy_manager_t));
    enemy_manager_t* em = *p_em;
    em->level = 1;
    em->wave_timer = timer;
    em->wave_load = 0;
    em->enemy_head = NULL;
}

game_t* init_game() {
    game_t* game = malloc(sizeof(game_t));
    game->money = 0;
    game->lives = 20;
    return game;
}

static void enemy_check_dead(){}
static int enemy_check_finish(enemy_t* p_em, game_t* game) {
    if(p_em->point.x == p_em->dest.x && p_em->point.y == p_em->dest.y) {
        game->lives--;
        return 1;
    }
    return 0;
}

//this function is proably getting too big for it's own good. whatever tho
static void enemy_move(enemy_t* p_e, enemy_t* prev, game_t* game) {
    //controls the clock mechanism to move enemies
    //tv_sec is the seconds since epoch, tv_nsec is the nanos on top of that.
    //I think this is the most efficent way. I'm not giogn to think too hard about how tooptimize it
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec;
    if(lm - p_e-> last_moved > p_e->move_timer) {
        //check before moving
        if(enemy_check_finish(p_e, game)) {
            despawn_enemy(game->e_manager,p_e,prev);
        }else{
            point_t move = astar(p_e->point, p_e->dest, game->map);
            p_e->point.x = move.x;
            p_e->point.y = move.y;
            p_e->last_moved = lm; 
        }
    }
}

void execute_em(game_t* game) {
    enemy_t* prev = NULL;
    enemy_t* p_e = game->e_manager->enemy_head;
    while(p_e != NULL) {
        //enemy death
        //enemy raeched the end
        //etc
        enemy_move(p_e, prev, game);
        prev = p_e;
        p_e = p_e->next;
    }
}

