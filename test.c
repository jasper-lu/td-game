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
    sing-> x = 100009;

    Node_heap * heapp = init_Node_heap();

    sing->parent = next;
    insert(sing, heapp);
    printf("%d",getMin(heapp)->x);

}
