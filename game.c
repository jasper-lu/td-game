#include <unistd.h>
#include "keyboard.h"
#include <stdlib.h>
#include "xterm_control.h" 
#include <stdio.h>
#include "game.h"
#define FPS 5

//prototypes
static void spawn_player(game_t* game);
static tower_t* spawn_tower(game_t* game, int type);
static enemy_t* spawn_enemy(game_t* game, int health, int speed);
static void draw_towers(game_t* game);
static void init_game(game_t* game);

static void init_game(game_t* game) {
    game = malloc(sizeof(game_t));
    game->money = 0;
}

static void init_map(game_t* game, int width, int height) {
//    printf("count\n");
    char ** map ;
     map = calloc(height+2, sizeof(char*));
    int i, j ;
    for(i = 0; i!= height + 2; ++i) {
        map[i] = calloc(width+2, sizeof(char));
        //put char here to cast as a boundary
    }
    for(i=0;i!= height + 2; ++i) {
        for(j=0;j!=width + 2; ++j) {
            if(i == 0 || j == 0 || i == height + 1 || i == width + 1)
                map[i][j] = 'x';
            else
                map[i][j] = ' ';
        }
    }


    game->map = map;
 //   printf("hi");
  //  printf("%c", map[0][0]);
   // printf("hi");
    //need to check if the map is correct

}

static void spawn_player(game_t* game) {
    game->player = (player_t){(point_t){0,0}};
}

static tower_t* spawn_tower(game_t* game, int type) {
    tower_t* temp_tower = malloc(sizeof(tower_t));
    *temp_tower = (tower_t) {(point_t) {game->player.point.x,game->player.point.y}, 10, 30, 0, TOWER, game->tower_head};
    game->tower_head = temp_tower;
    return temp_tower;
}

static enemy_t* spawn_enemy(game_t* game, int health, int speed) {
    enemy_t* temp_enemy = malloc(sizeof(enemy_t));
    //magic numers for starting point and ending point. will change eventually??
    *temp_enemy = (enemy_t) {(point_t) {0,4}, (point_t){19,5},speed,health,game->enemy_head};
    game->enemy_head = temp_enemy;
    return temp_enemy;
}

static void draw_towers(game_t* game) {
    tower_t* temp = game->tower_head;
    while(temp) {
        draw(&temp->point, get_sprite(temp->type));
        temp = temp->next;
    }
}

int main() {

    setbuf(stdout,NULL);
    game_t* game = malloc(sizeof(game_t)); 
    init_map(game, MAP_WIDTH, MAP_HEIGHT);
    char c;
    point_t point;
    spawn_player(game);
//    spawn_tower(game, TOWER);
    spawn_enemy(game,100,3);

    while(1)
    {
	while((c = getkey()) != KEY_NOTHING){

	
	if ((c == KEY_UP || c == 'w' )&& game->player.point.y > 0)
	{ 
	    xt_par2(XT_SET_ROW_COL_POS,game->player.point.y--,game->player.point.x);
	}
	else if ( c == 's' && game->player.point.y < MAP_HEIGHT - 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,game->player.point.y++,game->player.point.x);
	}
        //which means this is a 20*10 grid 
	else if ((c == KEY_RIGHT || c == 'd') && game->player.point.x < MAP_WIDTH - 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,game->player.point.y,game->player.point.x++);
	}
	else if ((c == KEY_LEFT || c == 'a') && game->player.point.x > 0)
	{
	    xt_par2(XT_SET_ROW_COL_POS,game->player.point.y,game->player.point.x--);
	}
	else if (c == '1')
	{
            spawn_tower(game, TOWER);
	}else if (c == 'r' || c == 'R')
	{
	}else if (c == ' '){
	} 
        }
//look into the clear screen function, and see if it can be adapted to only changet the playing aread
        

        /*
        char** map;
        map = malloc(sizeof(char*) * 5); 
        int i;
        for (i = 0;  i < 5; ++i)
	    map[i] = malloc(sizeof(char)*5);

        point_t new = astar((point_t){1,1}, (point_t){3,3}, map);
        printf("%d, %d", new.x, new.y);
        */
        //printf("%c", game->map[0][0]);

 //       printf("before astar");

        point_t move=  astar(game->enemy_head->point, game->enemy_head->dest, game->map);
        game->enemy_head->point.x = move.x;
        game->enemy_head->point.y = move.y;
 //       printf("after");

        xt_par0(XT_CLEAR_SCREEN);
        draw_ui();
        draw_towers(game);
        draw(&game->player.point, get_sprite(PLAYER));
        draw(&game->enemy_head->point, get_sprite(MONSTER));
        printf("enemy dest: %d, %d", game->enemy_head->dest.x, game->enemy_head->dest.y);

        xt_par2(XT_SET_ROW_COL_POS,999,999);

	usleep(1000000 / FPS);
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);


}
