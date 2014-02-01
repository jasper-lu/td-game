#include <unistd.h>
#include "keyboard.h"
#include <stdlib.h>
#include "xterm_control.h" 
#include <stdio.h>
#include "game.h"
#define FPS 20

static void draw_variables(game_t* game) {
    struct timespec temp;
    clock_gettime(CLOCK_REALTIME, &temp);
    long lm = temp.tv_sec * NANO + temp.tv_nsec; 
    SETPOS(MAP_WIDTH*TILE_WIDTH - 36, UI_DIST+2);
    printf("%d", game->e_manager->level);
    SETPOS(MAP_WIDTH*TILE_WIDTH - 36, UI_DIST+3);
    int countdown = (game->e_manager->wave_timer-(lm-game->e_manager->wave_load))/NANO +1 ;
    printf("%d", countdown);
    SETPOS(MAP_WIDTH*TILE_WIDTH - 36, UI_DIST+4);
    printf("%d", game->lives);
    SETPOS(MAP_WIDTH*TILE_WIDTH - 36, UI_DIST+5);
    printf("%d", game->money);

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
            if(i == 0 || j == 0 || i == height + 1 || j == width + 1 )
                map[i][j] = 'x';
            else
                map[i][j] = ' ';
        }
    }
    game->map = map;
    //need to check if the map is correct
}

int main() {

    char c;
    setbuf(stdout,NULL);
    //game_t* game = malloc(sizeof(game_t)); 
    game_t* game = init_game();
    //5 seconds to first spawn
    init_em(&game->e_manager, 3);
    init_map(game, MAP_WIDTH, MAP_HEIGHT);
    point_t point;
    spawn_player(game);
    //this is pissing me off, cause there are 10 of the monster bundled up here for some reason
    //set_spawn_wave(1, 10, game->e_manager);
    //bullets move 7x faster than the speed -- estimated width/height of everything
    //spawn_bullet(game,game->e_manager->enemy_head, (point_t){80,5}, 40, 20);

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

 //       printf("after");
        execute_bt(game);
        execute_em(game);
        execute_tw(game);

        xt_par0(XT_CLEAR_SCREEN);
        draw_ui();
        draw_variables(game);

        draw_towers(game);
        draw(tile_convert(&game->player.point), get_sprite(PLAYER));
        draw_bullets(game);
        draw_enemies(game);


        /*
        int i,j;
        for(i=0;i!= 11; ++i) {
         for(j=0;j!= 22; ++j) {
            putchar(game->map[i][j]);
        }
         printf("\n");
    }
    */

        xt_par2(XT_SET_ROW_COL_POS,999,999);

	usleep(1000000 / FPS);
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);


}
