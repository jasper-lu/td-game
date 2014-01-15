#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "keyboard.h"
#include "xterm_control.h" 
#define FPS 30

int main() {

    setbuf(stdout,NULL);

    int row = 1;
    int col = 1;
    char c;

    char* sprite[5] = {
        "-------",
        "| ^ ^ |", 
        "| 0 0 |", 
        "|     |", 
        "-------"
    };
    while(1)
    {
	if ((c = getkey()) == KEY_NOTHING){

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
	    xt_par2(XT_SET_ROW_COL_POS,row,col=col+2);
	}
	else if ((c == KEY_LEFT || c == 'A') && col > 1)
	{
	    xt_par2(XT_SET_ROW_COL_POS,row,col=col-2);
	}
	else if ((c == 'T' || c == 't') )
	{
	}else if (c == 'r' || c == 'R')
	{
	}else if (c == ' '){
	} 


	xt_par0(XT_CLEAR_SCREEN);
	xt_par2(XT_SET_ROW_COL_POS,row,col);
        printf(sprite[0]);
	xt_par2(XT_SET_ROW_COL_POS,row+1,col);
        printf(sprite[1]);
	xt_par2(XT_SET_ROW_COL_POS,row+2,col);
        printf(sprite[2]);
	xt_par2(XT_SET_ROW_COL_POS,row+3,col);
        printf(sprite[3]);
	xt_par2(XT_SET_ROW_COL_POS,row+4,col);
        printf(sprite[4]);
        xt_par2(XT_SET_ROW_COL_POS,999,999);

	usleep(1000000 / FPS);
    }
    getkey_terminate();

    xt_par0(XT_CLEAR_SCREEN);


}
