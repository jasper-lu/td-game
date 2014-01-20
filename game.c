#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "keyboard.h"
#include "xterm_control.h" 
#include "game.h"
#define FPS 30

//prototypes
static void spawn_player(game_t* game);
static tower_t* spawn_tower(game_t* game, int type);
static enemy_t* spawn_enemy(game_t* game, int health, int speed);

static void spawn_player(game_t* game) {
    game->player = (player_t){(point_t){2,2}};
}

static tower_t* spawn_tower(game_t* game, int type) {
    tower_t* temp_tower = malloc(sizeof(tower_t));
    *temp_tower = (tower_t) {(point_t) {game->player.point.x,game->player.point.y}, 10, 30, 0, TOWER, game->tower_head};
    game->tower_head = temp_tower;
    return temp_tower;
}

int main() {

    setbuf(stdout,NULL);

    game_t* game = malloc(sizeof(game_t));
    char c;
    point_t point;
    point.x = 1;
    point.y = 1;

    while(1)
    {
	if ((c = getkey()) == KEY_NOTHING){

	}
	else if ((c == KEY_UP || c == 'W' )&& point.y > 1)
	{ 
	    xt_par2(XT_SET_ROW_COL_POS,point.y-=4,point.x);
	}
	else if ((c == KEY_DOWN || c == 'S') && point.y < 36)
	{
	    xt_par2(XT_SET_ROW_COL_POS,point.y+=4,point.x);
	}
        //which means this is a 20*10 grid 
	else if ((c == KEY_RIGHT || c == 'D') && point.x < 133)
	{
	    xt_par2(XT_SET_ROW_COL_POS,point.y,point.x+=7);
	}
	else if ((c == KEY_LEFT || c == 'A') && point.x > 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,point.y,point.x-=7);
	}
	else if ((c == 'T' || c == 't') )
	{
	}else if (c == 'r' || c == 'R')
	{
	}else if (c == ' '){
	} 


	xt_par0(XT_CLEAR_SCREEN);
        draw(&point, get_sprite(PLAYER));
        xt_par2(XT_SET_ROW_COL_POS,999,999);

	usleep(1000000 / FPS);
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);


}
