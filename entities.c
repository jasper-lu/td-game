#include "entities.h"
#include <stdlib.h>

static char** bmap;
static void bmap_init() {
    int i,j;
    int height = TILE_HEIGHT * MAP_HEIGHT + 2;
    int width = TILE_WIDTH * MAP_WIDTH + 2;
    bmap = calloc(height, sizeof(char*));
    for(i = 0; i != height; ++i) {
        bmap[i] = calloc(width,sizeof(char));
    }
    for(i=0;i!= height; ++i) {
        for(j=0;j!=width; ++j) {
            if(i == 0 || j == 0 || i == height + 1 || j == width + 1 )
                bmap[i][j] = 'x';
            else
                bmap[i][j] = ' ';
        }
    }

}


void spawn_player(game_t* game) {
    game->player = (player_t){(point_t){0,0}};
}

void draw_towers(game_t* game) {
    tower_t* temp = game->tower_head;
    while(temp) {
        draw(tile_convert(&temp->point), get_sprite(temp->type));
        temp = temp->next;
    }
}

void draw_enemies(game_t* game) {
    enemy_t* temp = game->e_manager->enemy_head;
    while(temp) {
        draw(tile_convert(&temp->point), get_sprite(MONSTER));
        temp = temp->next;
    }

}

void draw_bullets(game_t* game) {
    bullet_t* bullet = game->bullet_head;
    while(bullet) {
        draw(bullet->point, get_sprite(BULLET));
        bullet = bullet->next;
    }
}

tower_t* spawn_tower(game_t* game, int type) {
    tower_t* temp_tower = malloc(sizeof(tower_t));
    int p_x = game->player.point.x;
    int p_y = game->player.point.y;
    //cooldown/fire timer

    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec;

    //2 times per second base?
    *temp_tower = (tower_t) {(point_t) {p_x, p_y}, 10, 2, 5, NANO/2, lm, TOWER, game->tower_head};
    char ** map = game->map;
    map[p_y+1][p_x+1] = 'x';
    game->tower_head = temp_tower;
    return temp_tower;
}

enemy_t* spawn_enemy(enemy_manager_t* em, int health, int speed) {
    enemy_t* temp_enemy = malloc(sizeof(enemy_t));
    //magic numers for starting point and ending point. will change eventually??
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec;
    *temp_enemy = (enemy_t) {(point_t) {0,4}, (point_t){19,4},NANO/speed,lm,health,em->enemy_head};
    em->enemy_head = temp_enemy;
    return temp_enemy;
}

//bullet spawn. bullet coord system is different from the others, in that it is pixel-based rather than tile-based
bullet_t* spawn_bullet(game_t* game, enemy_t* target, point_t point, int damage, int speed) {
    bullet_t* temp_bullet = malloc(sizeof(bullet_t));
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec;
    *temp_bullet = (bullet_t) {(point_t){point.x,point.y}, damage, NANO/(speed*7), lm, target, game->bullet_head};
    //bullet chain in game
    game->bullet_head = temp_bullet;
    return temp_bullet;
}

//ben kurtovic thanks. Way to despawn without being overly complicated
bullet_t* despawn_bullet(bullet_t* bullet, bullet_t* prev, game_t* game) {
    bullet_t* next = bullet->next;
    if(prev){
        //printf("wrong");
        prev->next = next;
    }else{
        //printf("head is next\n");
        game->bullet_head = next;
    }
    free(bullet);
    //    bullet = NULL;
    return next;
}

enemy_t* despawn_enemy(enemy_t* enemy, enemy_t* prev, enemy_manager_t* em) {
    enemy_t* next = enemy->next;
    if (prev)
        prev->next = next;
    else
        em->enemy_head = next;
    free(enemy);
    return next;
}

void init_em(enemy_manager_t** p_em, int timer) {
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec;
    *p_em = calloc(sizeof(enemy_manager_t), 1);
    enemy_manager_t* em = *p_em;
    em->level = 1;
    long l_temp = NANO;
    printf("%ld", l_temp);
    //spawn in timer seconds
    em->wave_timer = (long)NANO*timer;
    em->wave_load = lm;
    printf("wave_tiemr: %ld", em->wave_timer);
    printf("\n%ld x %ld = %ld\n", NANO, timer, (long)NANO*timer);
    printf("wave_load: %ld", em->wave_load);
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
            despawn_enemy(p_e,prev,game->e_manager);
        }else{
            point_t move = astar(p_e->point, p_e->dest, game->map);
            p_e->point.x = move.x;
            p_e->point.y = move.y;
            p_e->last_moved = lm; 
        }
    }
}

static void dmg_enemy(enemy_t* enemy, int dmg) {
    enemy->health -= dmg;
}

static int bullet_collision(bullet_t* p_b, bullet_t* prev, point_t dest, game_t* game) {
    if(p_b->point.x == dest.x && p_b->point.y == dest.y) {
        dmg_enemy(p_b->target, p_b->dmg);
        despawn_bullet(p_b, prev, game);
        return 1;
    }
    return 0;
}

static void bullet_move(bullet_t* p_b, bullet_t* prev, point_t dest, game_t* game) {
    if(!bmap)
        bmap_init();
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec; 
    if(lm - p_b->last_moved > p_b->move_timer) { 
        //printf("bullet astar before\n");
        //printf("%d",p_b->point.x);
        //printf("%d",dest.x);
        point_t move = astar(p_b->point, dest, bmap);
        //printf("bullet astar after\n");
        p_b->point.x = move.x;
        p_b->point.y = move.y;
        p_b->last_moved = lm;
    } 
} 


//contains all bullet actions, i.e. collision checking, and movement
void execute_bt(game_t* game) {
    bullet_t* prev = NULL;
    bullet_t* p_b = game->bullet_head; 
    while(p_b != NULL) { 
        point_t targ = tile_convert(&p_b->target->point);
        if(bullet_collision(p_b, prev, targ, game)) {
            break;
        }
        bullet_move(p_b,prev,targ,game);
        prev = p_b;
        p_b = p_b->next;
    }
    //check all the enemies for deaths here
    p_b = game->bullet_head; 
    prev = NULL;
    while(p_b != NULL) {
        //this may cause the game to crash in some places. cross fingers and hope
        if(p_b->target->health <= 0)
            p_b = despawn_bullet(p_b, prev, game);
        else{
            prev = p_b;
            p_b = p_b->next;
        }
    }
    //printf("nope");
}

static void spawn_wave(enemy_manager_t* em) {
    if(em->spawn_numb) {
        struct timespec temp;
        clock_gettime(CLOCK_REALTIME, &temp);
        long lm = temp.tv_sec * NANO + temp.tv_nsec; 
        if(lm -em->last_moved >=NANO/ em->speed) { 
            spawn_enemy(em, em->health, em->speed);
            em->last_moved = lm;
            em->spawn_numb--;
        }
    }
}

static void spawn_wave_check(enemy_manager_t* em) {
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec; 
 
    if( lm-em->wave_load > em->wave_timer ) {
    printf("lhs : %lu; rhs: %lu FEIWGIEWG\n",em->wave_load, em->wave_timer);
        //really dumb scaling algorithm whoops shoot me
       printf("spawn wave setYOYOYO");
        int i = em->level;
        if(i%2) {
  //          printf("hi");
            //set spawn to scale sped 
            set_spawn_wave(em->level/2 + 1, i * 10, 5, em);
        }else{
   //         printf("o");
            set_spawn_wave(em->level/2 + 1, i*10 + 10, 5, em);
        }
        em->wave_load = lm;
    }
}

void execute_em(game_t* game) {
    enemy_t* prev = NULL;
    enemy_t* p_e = game->e_manager->enemy_head;
    while(p_e != NULL) {
        //enemy death
        //enemy raeched the end
        //etc
        if(p_e->health <= 0) {
            p_e = despawn_enemy(p_e, prev, game->e_manager);
            return;
        }else{
            enemy_move(p_e, prev,game);
            prev = p_e;
            p_e = p_e->next;
        }
    }
    spawn_wave_check(game->e_manager);
    spawn_wave(game->e_manager);
}

static int in_range(point_t* center, point_t* node, int r) {
    return abs(center->x - node->x) <= r && abs(center->y - node->y) <= r;
}

void set_spawn_wave(int speed, int health, int spawn_numb, enemy_manager_t* em) {
    printf("spawn wave set");
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec;
    em->spawn_numb = spawn_numb;
    //this one will have the thing be wonky
    printf("the speed is: %lu\n", em->speed);
    em->speed = speed;
    em->last_moved = lm;
    em->health = health;
}

void execute_tw(game_t* game) {
    tower_t* p_t = game->tower_head;
    enemy_t* p_e;
    while(p_t != NULL) { 
        //the following lines, as in all the other execute functions, checks if the timer is good and then folllows through
        struct timespec temp;
        clock_gettime(CLOCK_REALTIME, &temp);
        long lm = temp.tv_sec * NANO + temp.tv_nsec; 
        if(lm - p_t->cooldown_timer > p_t->cooldown) { 
            p_e = game->e_manager->enemy_head;
            while(p_e != NULL) {
                if(in_range(&p_t->point,&p_e->point,p_t->radius)) {
                    spawn_bullet(game, p_e, tile_convert(&p_t->point), p_t->power, p_t->b_speed);
                    break;
                }
                p_e = p_e->next;
            }
            p_t->cooldown_timer = lm;
        }
        p_t = p_t->next;
    }
}
