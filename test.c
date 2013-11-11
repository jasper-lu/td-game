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
    sing-> f = 9;
    next-> x = 19;

    Node_heap * heapp = init_Node_heap();

    sing->parent = next;
    insert(sing, heapp);
    insert(next, heapp);
    printf("%d",getMin(heapp)->x);

}
