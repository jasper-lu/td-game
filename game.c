#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "keyboard.h"
#include "xterm_control.h" 
#include "graphics.h"
#define FPS 30

int main() {

    setbuf(stdout,NULL);

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
