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


    Node *a = init_Node();
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
    /*
    insert(d, heapp);
    insert(e, heapp);
    */
     
    printf("%d\n",pop(heapp)->f);
    printf("%d\n",pop(heapp)->f);
    /*
    printf("%d\n",removeMin(heapp)->f);
    printf("%d\n",removeMin(heapp)->f);
    printf("%d\n",removeMin(heapp)->f);
    */
}
