#include <stdio.h>
#include "xterm_control.h"
#include <time.h>

void wait() 
{
    clock_t endwait;
    endwait = clock() + (.1 * CLOCKS_PER_SEC);
    while(clock() < endwait){}
}
