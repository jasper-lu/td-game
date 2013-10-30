#include <stdio.h>
#include "keyboard.h"
#include "structs.h"
#include "launch.h"
#include "xterm_control.h"

void main (int argc, char * argv[]) {
    mob bob;

    map_init();

    char *map[24][80] = {' '}; 

    char c = ' ';
    int row = 1,col = 1;

    xt_par2(XT_SET_ROW_COL_POS,row=1,col=1);

    while(1) {
	while ((c = getkey()) == KEY_NOTHING) ;
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
    }
}

