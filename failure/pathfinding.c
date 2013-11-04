#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define EXIT 'O'
#define WALL 'X'
#include "structs.h"
#include "pathfinding.h"
#include <stdio.h>

point init_point(int x, int y)
{
    point r;
    r.x = x;
    r.y = y;
    return r;
}

int depth_move(point curr, char map[ROWS][COLS]) 
{
    int dir;
    if(dir = depth_moveh(init_point(curr.x,curr.y+1),DOWN,map))
	return dir;
    else if(dir = depth_moveh(init_point(curr.x + 1,curr.y),RIGHT,map))
	return dir;
    else if(dir = depth_moveh(init_point(curr.x,curr.y-1),UP,map))
	return dir;
    else if(dir = depth_moveh(init_point(curr.x-1,curr.y),LEFT,map))
	return dir;
}

int depth_moveh(point next, int dir, char map[ROWS][COLS]) 
{
    int ret;
    char c = map[next.y][next.x];
    if (c == 'X'){
	return 0;
    }
    if (c == 'O')
	return dir;	
    if(dir == UP)
	printf("up");
    if(dir == DOWN)
	printf("down");

    if (dir != UP && depth_moveh(init_point(next.x, next.y+1), DOWN, map)){ 
	return dir;
    }
    else if (dir != RIGHT && depth_moveh(init_point(next.x-1,next.y), LEFT, map))
	return dir;
    else if (dir != DOWN && depth_moveh(init_point(next.x,next.y-1), UP, map))
	return dir;
    else if (dir != LEFT && depth_moveh(init_point(next.x+1, next.y), RIGHT, map))
	return dir;
    /*
    else if (dir != UP)
	printf("hihiiihi");
	*/
    return 0;
}

/*
   direction direction(point start, int dir_from, char [][] map)
   {
//THIS IS AN INFINITE LOOOP
//add something that records the direction coming fom
switch (map[start.dir.x][start.dir.y])
{
case 'X':
return -1;
case 'O':
return 0;
default:
;
}

point l = start,r = start,u = start, d = start;
l.dir.x--;
r.dir.x++;
d.dir.y--;
u.dir.y++;

if(dir_from != LEFT)
l = direction(l,map);
if(dir_from != RIGHT)
r = direction(r,map);
if(dir_from != DWON)
u = direction(d,map);
if(dir_from != UP)
d = direction(u,map);

direction ret = min(left,right,up,down);
ret.score++;

return ret;
}

direction min(direction l, direction r, direction u, direction d)
{
direction n1, n2;
if (l.score > r.score)
n1 = l;
else
n1 = r;

if (u.score > d.score)
n2 = u;
else
n2 = d;

if (n1 > n2)
return n1;
else
return n2;
}
*/
