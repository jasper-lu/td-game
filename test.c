#include <stdio.h>
#include <unistd.h>
#include "structs.h"
#include "launch.h"
#include "keyboard.h"
#include "xterm_control.h" 

int main() {
    Mob MOBS[10];
    char map[10][20] = {
	{'X',' ','O',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
	{'X',' ',' ',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
	{'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X'},
	{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',' ',' ',' ','X','X'},
	{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',' ',' ',' ','X','X'},
	{'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X',' ',' ',' ','X','X'},
	{'X',' ',' ',' ','X','X','X','X','X','X',' ',' ',' ','X','X',' ',' ',' ','X','X'},
	{'X',' ',' ',' ','X','X','X','X','X','X',' ',' ',' ',' ',' ',' ',' ',' ','X','X'},
	{'X',' ',' ',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
	{'X',' ','O',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
    };
    MOBS[0] = init_mob(2,1);

    int r, c;

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,r=1,c=1);

    for(r = 0; r < 10; ++r)
    {
	for(c = 0; c < 20; ++c)
	    putchar(map[r][c]); printf("\n");
    }

    int row = 1;
    int col = 1;
    xt_par2(XT_SET_ROW_COL_POS,row,col);

    while(1)
    {
	while ((c = getkey()) == KEY_NOTHING) ;
	if(c == KEY_F9) 
	{
	    xt_par0(XT_CLEAR_SCREEN);
	    xt_par2(XT_SET_ROW_COL_POS,row=1,col=1);
	    break;
	}
	else if (c == KEY_UP && row > 1)
	{ 
	    xt_par2(XT_SET_ROW_COL_POS, MOBS[0].y + 1,MOBS[0].x + 1);
	    putchar('M');
	    if(move_mob(&MOBS[0]))
		break;
	    xt_par2(XT_SET_ROW_COL_POS,--row,col);
	}
	else if (c == KEY_DOWN && row < 24)
	{
	    xt_par2(XT_SET_ROW_COL_POS, MOBS[0].y + 1,MOBS[0].x + 1);
	    putchar('M');
	    if(move_mob(&MOBS[0]))
		break;
	    xt_par2(XT_SET_ROW_COL_POS,++row,col);
	}
	else if (c == KEY_RIGHT && col < 80)
	{
	    xt_par2(XT_SET_ROW_COL_POS, MOBS[0].y + 1,MOBS[0].x + 1);
	    putchar('M');
	    if(move_mob(&MOBS[0]))
	       	break; 
	    xt_par2(XT_SET_ROW_COL_POS,row,++col);
	}
	else if (c == KEY_LEFT && col > 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS, MOBS[0].y + 1,MOBS[0].x + 1);
	    putchar('M');
	    if(move_mob(&MOBS[0]))
		break;
	    xt_par2(XT_SET_ROW_COL_POS,row,--col);
	}
    }

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,1,1);

}
