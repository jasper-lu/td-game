#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "astar.h"
#include "structs.h"
#include "keyboard.h"
#include "xterm_control.h" 
#include "game_init.h"

int main() {

    setbuf(stdout,NULL);

    Point begin = init_Point(1,1);
    Point finish = init_Point(18,8);

    Mob * MOBS;

    char **map;
    map = malloc(sizeof(char*) * ROWS); 

    int i,Score;
    for (i = 0;  i < COLS + 2; ++i)
	map[i] = malloc(sizeof(char) * (COLS + 2));

    MOBS = malloc(sizeof(Mob) * 100);
    int mob_size = 0;

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,1,1);

    init_map(map, ROWS, COLS);
    Tower* arr;
    i = 0;
    arr = malloc(sizeof(Tower) * 100);

    int row = 1;
    int col = 1;
    xt_par2(XT_SET_ROW_COL_POS,row,col);

    char c;


    printf("Before game loop \n");

    int move_c = 0;
    int wave_start = 0;
    int next_wave_total = 1;
    int spawn_count = 0;

    while(1)
    {
	if ((c = getkey()) == KEY_NOTHING){

	}
	else if(c == KEY_F9) 
	{
	    xt_par0(XT_CLEAR_SCREEN);
	    xt_par2(XT_SET_ROW_COL_POS,row=1,col=1);
	    break;
	}
	else if ((c == KEY_UP || c == 'W' )&& row > 1)
	{ 
	    xt_par2(XT_SET_ROW_COL_POS,--row,col);
	}
	else if ((c == KEY_DOWN || c == 'S') && row < 24)
	{
	    xt_par2(XT_SET_ROW_COL_POS,++row,col);
	}
	else if ((c == KEY_RIGHT || c == 'D') && col < 80)
	{
	    xt_par2(XT_SET_ROW_COL_POS,row,++col);
	}
	else if ((c == KEY_LEFT || c == 'A') && col > 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,row,--col);
	}
	else if ((c == 'T' || c == 't') )
	{
	    putchar('T');
	    map[row - 1][col - 1] = 'T';
	    Tower A = init_Tower(col-1,row-1);
	    arr[i] = A;
	    i++;
	}else if (c == 'r')
	{
	    if(wave_start == 0)
	    {
		spawn_count = next_wave_total;
		++wave_start;
	    }
	}


	if(wave_start == 1)
	{
	    if(move_c == 3)
	    {
		move_mob(MOBS, mob_size, &finish, map);
		if(spawn_count != 0)
		    spawn_count = spawn(MOBS, &mob_size, begin, spawn_count);
		move_c = 0;

		if(round_won(MOBS, &mob_size))
		{
		    next_wave_total++;
		    wave_start = 0;
		}
	    }else{
		++move_c;
	    }
	    if(i > 0)
		tower_logic(arr, MOBS, i,mob_size);
	}

	xt_par0(XT_CLEAR_SCREEN);
	xt_par2(XT_SET_ROW_COL_POS,1,1);

	draw_map(map, ROWS, COLS, arr, i, MOBS, mob_size);

	xt_par2(XT_SET_ROW_COL_POS, MOBS[0].y + 1,MOBS[0].x + 1);


	xt_par2(XT_SET_ROW_COL_POS, row,col);

	xt_par2(XT_SET_ROW_COL_POS, 15, 0);
	printf("Score:%d\n size of : %d\n",Score,i);      
	xt_par2(XT_SET_ROW_COL_POS, row,col);

	if(loser(MOBS, &finish))
	{
	    printf("YOU LOSE,\n LOSER\n TRY AGAIN NEXT TIME \n");
	    //	  usleep(3000000);
	    break;
	}

	usleep(1000000 / FPS);
	//	usleep(1000000);
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,1,1);


    free(MOBS);
    free(arr);
}
