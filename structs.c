#include "structs.h"

static int PATH[] = {D,R,R,R,R,R,R,R,R,R,R,R,R,R,R,D,D,D,D,D,L,L,L,L,L,U,U,L,L,L,L,L,L,L,L,L,D,D,D,D};

Mob init_mob(int x, int y)
{ 
    Mob r; 
    r.x = x; 
    r.y = y;
    r.health = 3;
    r._n = 0;
    return r;
}

int move_mob(Mob *mob)
{
    switch (PATH[mob->_n])
    {
	case U:
	    --(mob->y);
	    break;
	case R:
	    ++(mob->x);
	    break;
	case D:
	    ++(mob->y);
	    break;
	case L:
	    --(mob->x);
	    break;
    }
    ++(mob->_n);
    if(mob->_n == 42)
	return 1;
    else
	return 0;
}
