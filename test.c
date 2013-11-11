#include "stdlib.h"
#include "stdio.h"
#include "astar.h"

int main ()
{
    char map[3][3] = {
	{'O',' ',' '},
	{' ',' ',' '},
	{' ',' ','O'}
    };
    Node *sing=init_Node();
    Node *next=init_Node();

   sing->parent = next;

//    Node_heap * heapp = init_Node_heap();
 //   insert(blah, heapp);
	printf("|%d|",sing->x);
	printf("|%d|",next->x);
	printf("|%d|",sing->parent->y);
	printf("|%d|",sing->parent->f);
}
