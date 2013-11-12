#include "structs.h"
#include "math.h"
#include "astar.h"


static int Score = 0;

Mob init_mob(int x, int y)
{ 
    Mob r; 
    r.x = x; 
    r.y = y;
    r.health = 100;
    r._n = 0;
    return r;
}

void move_mob(Mob *mob, int mob_size, struct Point* end, char **map)
{
    /*
    int i; for(i = 0; i <= mob_size; ++i)
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
    */
    //printf("astar\n");
    Point b = astar(init_Point(mob->x,mob->y),*end,map);
    //printf("astar after \n");
    mob->x = b.x;
    mob->y = b.y;
}

Tower init_Tower(int x, int y)
{
    Tower A; 
    A.x = x; A.y = y; A.dmg = 10;
    return A;
}

void tower_logic(Tower *a, Mob *b, int mob_size)
{
    int n;
    for(n = 0; n != mob_size; ++n)
    {
	if(b->health > 0 && abs(a->x - b-> x) <= 2 && abs(a->y - b->y) <=2)
	{
	    b->health = b->health - a->dmg;
	    if (b->health == 0)
		Score += 10;
	}
	++b;
    } 
}

int loser(Mob* mob, struct Point* end)
{
    if(mob[0].x == end->x && mob[0].y == end->y)
	return 1;
    else
	return 0;
}
