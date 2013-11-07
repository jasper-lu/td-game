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
    MOBS[0] = init_mob(2,1);

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,1,1);

    init_map(map, ROWS, COLS);

    int row = 1;
    int col = 1;
    xt_par2(XT_SET_ROW_COL_POS,row,col);

    char c;

    while(1)
    {
	while ((c = getkey()) == KEY_NOTHING){
	    xt_par2(XT_SET_ROW_COL_POS, MOBS[0].y + 1,MOBS[0].x + 1);
	    putchar('M');
	    usleep(1000000 / FPS);
	    move_mob(&MOBS[0]);
	    xt_par2(XT_SET_ROW_COL_POS, row, col);
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
	if(*map[MOBS[0].y, MOBS[0].x] == 'O')
	    break;
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,1,1);

}
