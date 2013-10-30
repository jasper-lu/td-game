#include <stdio.h>
#include "xterm_control.h"
#include <time.h>

void wait();

void map_init()
{
    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS,1,1);
    FILE *fp;
    fp = fopen("map.jl","r");
    char lines[200];
    while(fgets(lines,199,fp))
    {
	wait();
	printf(lines);
    }
    fclose(fp);
    xt_par2(XT_SET_ROW_COL_POS,1,1);
}

void wait() 
{
    clock_t endwait;
    endwait = clock() + .5 * CLOCKS_PER_SEC;
    while(clock() < endwait){}
}
