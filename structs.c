#include "structs.h"
#include "math.h"

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

void move_mob(Mob *mob, int mob_size)
{
    int i;
    for(i = 0; i <= mob_size; ++i)
    {
	if(mob->_n < 40)
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
	}
	++i;
    }
}

void tower_logic(Tower *a, Mob *b, int mob_size)
{
    int n;
    for(n = 0; n != mob_size; ++n)
    {
	if(b->health > 0 && abs(a->x - b-> x) <= 2 && abs(a->y - b->y) <=2)
	{
	    --(b->health);
	    if (b->health == 0)
		a->score += 10;
	}
    } 
}
