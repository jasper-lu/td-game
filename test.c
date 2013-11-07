#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "structs.h"
#include "launch.h"
#include "keyboard.h"
#include "game_init.h"
#include "xterm_control.h" 

int main() {

    fflush(stdout);
    Mob MOBS[10];

    char **map;
    map = malloc(sizeof(char*) * ROWS); 

    int i;
    for (i = 0;  i < COLS + 2; ++i)
	map[i] = malloc(sizeof(char) * (COLS * 2));

    MOBS[0] = init_mob(2,1);

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,1,1);

    init_map(map, ROWS, COLS);
    Tower* arr;
    arr = malloc(sizeof(Tower) * 10);

    int row = 1;
    int col = 1;
    xt_par2(XT_SET_ROW_COL_POS,row,col);

    char c;

    while(1)
    {
	while ((c = getkey()) == KEY_NOTHING){

	    xt_par0(XT_CLEAR_SCREEN);
	    xt_par2(XT_SET_ROW_COL_POS,1,1);
	    move_mob(&MOBS[0]);

	    draw_map(map, ROWS, COLS);

	    xt_par2(XT_SET_ROW_COL_POS, MOBS[0].y + 1,MOBS[0].x + 1);

	    putchar('M');

	    xt_par2(XT_SET_ROW_COL_POS, row,col);
	    usleep(1000000 / FPS);
	} ;

	if(c == KEY_F9) 
	{
	    xt_par0(XT_CLEAR_SCREEN);
	    xt_par2(XT_SET_ROW_COL_POS,row=1,col=1);
	    break;
	}
	else if (c == KEY_UP && row > 1)
	{ 
	    xt_par2(XT_SET_ROW_COL_POS,--row,col);
	}
	else if (c == KEY_DOWN && row < 24)
	{
	    xt_par2(XT_SET_ROW_COL_POS,++row,col);
	}
	else if (c == KEY_RIGHT && col < 80)
	{
	    xt_par2(XT_SET_ROW_COL_POS,row,++col);
	}
	else if (c == KEY_LEFT && col > 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,row,--col);
	}
	else if (c == 'T' || c == 't'  && map[row][col] == 'X')
	{
	    putchar('T');
	    Tower A;
	    A.x = col;
	    A.y = row;
	    arr[i] = A;
	    i++;
	}
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,1,1);

}
