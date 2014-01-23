#include "stdlib.h"
#include "stdio.h"
#include "astar.h"
#include "structs.h"
#define ROWS 10
#define COLS 20

int main ()
{
    char ** map;
    map = malloc(sizeof(char*) * ROWS);
    int i;
    for(i = 0; i < COLS +2; ++i)
    {
	map[i] = malloc(sizeof(char) * (COLS + 2));
    }    

    FILE *fp;
    fp = fopen("map.txt", "r");
    char ch;

    int j;

    for(i = 0; i < ROWS; i++)
    {
	for(j = 0; j < COLS + 1; j++)
	{
	    ch = fgetc(fp);
	    map[i][j] = ch;
	}
    }

//    printf("map 0,1: %c",map[1][0]);
    fclose(fp);

    Point s = init_Point(1,1);
    Point e = init_Point(2,8);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    s = astar(s,e,map);
    printf("%d,%d : \n",  s.x,s.y);
    /*
       Node *a = init_NodeP(init_Point(3,5));
       Node *b = init_Node();
       Node *c = init_Node();
       Node *d = init_Node();
       Node *e = init_Node();

       a->f = 3;
       b->f = 5;
       c->f = 1;
       d->f = 4;
       e->f = 4;

       Node_heap * heapp = init_Node_heap();

       insert(a, heapp);
       insert(b, heapp);
       insert(c, heapp);
       insert(d, heapp);
       insert(e, heapp);
       printf("%d\n",pop(heapp)->f);
       printf("%d\n",pop(heapp)->f);
       printf("%d\n",pop(heapp)->f);
       printf("%d\n",pop(heapp)->f);
       printf("%d\n",pop(heapp)->f);

       Point f, g;
       f.x = 3;
       f.y = 3;
       g.x = 3;
       g.y = 3;
       if(p_equals(f,g))
       printf("hihhi");
       */
}
