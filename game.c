#include <unistd.h>
#include "keyboard.h"
#include <stdlib.h>
#include "xterm_control.h" 
#include <stdio.h>
#include "game.h"
#define FPS 30

//prototypes
static void spawn_player(game_t* game);
static tower_t* spawn_tower(game_t* game, int type);
static enemy_t* spawn_enemy(game_t* game, int health, int speed);
static void draw_towers(game_t* game);

static void spawn_player(game_t* game) {
    game->player = (player_t){(point_t){0,0}};
}

static tower_t* spawn_tower(game_t* game, int type) {
    printf("1");
    tower_t* temp_tower = malloc(sizeof(tower_t));
    printf("2");
    *temp_tower = (tower_t) {(point_t) {game->player.point.x,game->player.point.y}, 10, 30, 0, TOWER, game->tower_head};
    printf("3");
    game->tower_head = temp_tower;
    printf("4");
    return temp_tower;
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
    char c;
    point_t point;
    spawn_player(game);
//    spawn_tower(game, TOWER);

    while(1)
    {
	if ((c = getkey()) == KEY_NOTHING){

	}
	else if ((c == KEY_UP || c == 'W' )&& game->player.point.y > 0)
	{ 
	    xt_par2(XT_SET_ROW_COL_POS,game->player.point.y--,game->player.point.x);
	}
	else if ((c == KEY_DOWN || c == 'S') && game->player.point.y < MAP_HEIGHT - 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,game->player.point.y++,game->player.point.x);
	}
        //which means this is a 20*10 grid 
	else if ((c == KEY_RIGHT || c == 'D') && game->player.point.x < MAP_WIDTH - 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,game->player.point.y,game->player.point.x++);
	}
	else if ((c == KEY_LEFT || c == 'A') && game->player.point.x > 0)
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
//look into the clear screen function, and see if it can be adapted to only changet the playing aread
	xt_par0(XT_CLEAR_SCREEN);
        draw_ui();
        draw_towers(game);
        draw(&game->player.point, get_sprite(PLAYER));

        xt_par2(XT_SET_ROW_COL_POS,999,999);

	usleep(1000000 / FPS);
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);


}
