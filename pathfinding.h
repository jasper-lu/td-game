#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define EXIT 'O'
#define WALL 'X'

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
