#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "keyboard.h"
#include "xterm_control.h" 
#include "graphics.h"
#define FPS 30

int main() {

    setbuf(stdout,NULL);

    int row = 1;
    int col = 1;
    char c;

    while(1)
    {
	if ((c = getkey()) == KEY_NOTHING){

	}
	else if ((c == KEY_UP || c == 'W' )&& row > 1)
	{ 
	    xt_par2(XT_SET_ROW_COL_POS,row=row-4,col);
	}
	else if ((c == KEY_DOWN || c == 'S') && row < 36)
	{
	    xt_par2(XT_SET_ROW_COL_POS,row=row+4,col);
	}
        //which means this is a 20*10 grid 
	else if ((c == KEY_RIGHT || c == 'D') && col < 133)
	{
	    xt_par2(XT_SET_ROW_COL_POS,row,col=col+7);
	}
	else if ((c == KEY_LEFT || c == 'A') && col > 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,row,col=col-7);
	}
	else if ((c == 'T' || c == 't') )
	{
	}else if (c == 'r' || c == 'R')
	{
	}else if (c == ' '){
	} 


	xt_par0(XT_CLEAR_SCREEN);

        xt_par2(XT_SET_ROW_COL_POS,999,999);

	usleep(1000000 / FPS);
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);


}
