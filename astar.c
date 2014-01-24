#include "astar.h"
#include <math.h>
#include <stdlib.h>

//Creates a new node altogether
Node* init_Node()
{
    Node* node;
    node = malloc(sizeof(Node));
    node->p.x=0;node->p.y=0;node->f=0;node->h=0;node->parent = NULL;
    return node;
}

//Initiates a node for a pre-existing point
Node* init_NodeP(point_t p)
{
    Node *node;
    node = malloc(sizeof(Node));
    node->p = p;
    node->f = 0;
    node->h = 0;
    node->parent = NULL;
}

//inits node for existing point and parent, so for a score.
Node* init_NodeA(point_t p, int f, int h, Node* parent)
{
    Node* node;
    node = malloc(sizeof(Node));
    node->p = p; node->f = f; node->h = h; node->parent = parent;
}

//self-explanatory. initializes the Node Heap
Node_heap* init_Node_heap()
{
    Node_heap *heap = malloc(sizeof(Node_heap)); 
    heap->heap = malloc(sizeof(Node) * 180);
    heap->size = 0;
    return heap;
}


int compare(Node* lhs, Node * rhs)
{
    return (lhs->f + lhs->h) - (rhs->f + rhs->h);
}

//holy shit this code was written so long ago i dont eevn remember it anymore....i'm going to assume it is magic. NTS: comment code more in the future
void insert(Node *x, Node_heap* heap)
{
        heap->size++;
        heap->heap[heap->size] = x; 
        int now = heap->size;
	while(now > 1 && compare(heap->heap[now/2], x) > 0)
        {
                heap->heap[now] = heap->heap[now/2];
                now /= 2;
        }
        heap->heap[now] = x;
}

void swap(Node **a, Node **b)
{
    Node **temp = a;
    a = b;
    b = temp;
}

Node* pop(Node_heap * heap)
{
        Node* minElement;
	Node* lastElement;
	int now, child;
        minElement = heap->heap[1];
        lastElement = heap->heap[heap->size];
	heap->size--;
        for(now = 1; now*2 <= heap->size ;now = child)
        {
                child = now*2;
                if(child != heap->size && compare(heap->heap[child+1],heap->heap[child]) < 0) 
                {
                        child++;
                }
                if(compare(lastElement,heap->heap[child]) > 0)
                {
                        heap->heap[now] = heap->heap[child];
                }
                else 
                {
                        break;
                }
        }
        heap->heap[now] = lastElement;
        return minElement;
}

Node* getMin(Node_heap *heap)
{
    return heap->heap[1];
}

//end magic code stuff
int close_heap(Node_heap *heap) { 
    int i;
    for(i = 1; i <= heap->size; ++i)
	free(heap->heap[i]);
    free(heap->heap);
    free(heap);
}

int p_equals(point_t lhs, point_t rhs)
{
    if(lhs.x == rhs.x && lhs.y == rhs.y)
	return 1;
    else
	return 0;
}
//fuck some more magic code....
int add_neighs(point_t home, point_t* neigh, char **map)
{
//    printf("adding neigh\n");
    int n = 0;
//	printf("and one %d, %d\n", home.x,home.y);
    if(map[home.y+1][home.x] != 'x' )
    {
	neigh[n++] = (point_t){home.x,home.y+1};
//	printf("and two\n");
    }
    if(map[home.y][home.x+1] != 'x' )
    {
//	printf("and 3\n");
	neigh[n++] = (point_t){home.x+1,home.y};
    }
    if(map[home.y-1][home.x] != 'x' )
    {
//	printf("and 4\n");
	neigh[n++] = (point_t){home.x,home.y-1};
    }
    if(map[home.y][home.x-1] != 'x' )
    {
//	printf("and 5\n");
	neigh[n++] = (point_t){home.x-1,home.y};
    }

//    printf("addneights this round: %d\n", n);
    return n;
}

int calcH(point_t curr, point_t end)
{
    return abs(end.x - curr.x) + abs(end.y - curr.y);
}

int isIn(Node** in, int size, point_t p)
{
    int n;
  //  printf("start\n");
    for(n = 0;n<= size; ++n)
    {
	//if it doesnt go past size
//	printf("P works -- %d %d \n", p.x, p.y);
	if(n!=0)
//	    printf("heap works -- %d %d \n", in[n]->p.x,in[n]->p.x);
	if(in[n] != NULL && p_equals(in[n]->p,p))
	    return 1;
    }
 //   printf("yolo\n");
    return 0;
}

point_t astar(point_t begin, point_t end, char** map)
{
    //some horribly written code to fix the transition mistakes, namely, map is formatted with 1,1 being hte first open spot vs the entity point class having 0,0 being the first
    begin.x++;
    begin.y++;
    end.x++;
    end.y++;
    //endfix
    Node *start = init_NodeA(begin, 0, calcH(begin,end),NULL); 
    Node_heap *open = init_Node_heap();
    insert(start, open);
    Node** closed = malloc(sizeof(Node) * 200);
    int n =0;
    while(!(p_equals(getMin(open)->p,end)))
    {
        //printf("\n\nworks up to this place \n");
	Node* current = pop(open);
        //printf("\n\nworks beforeh ere too \n");
	closed[n] = current;
	++n;
	point_t* neighs = malloc(sizeof(point_t) * 4);
	int neigh_size = add_neighs(current->p,neighs,map);
	int c;

	int cost = current->f + 1;

	for(c = 0; c != neigh_size; ++c)
	{
	    if(!(isIn(open->heap, open->size,neighs[c])) && !(isIn(closed,n-1,neighs[c])))
	    {
        //        printf("hueristic for %d -- %d,%d: %d", c, neighs[c].x, neighs[c].y, calcH(neighs[c], end));
		Node* neigh = init_NodeA(neighs[c],cost,calcH(neighs[c],end),current);
        //        printf("one two \n");
		insert(neigh,open);
	    }
	}
	free(neighs);
//        printf("out?");
    }
    Node * final = pop(open);
    while(!(p_equals(final->parent->p, begin)))
    {
	final = final->parent;
    }

    point_t ret = (point_t) {final->p.x, final->p.y};

    int close_c;
    
    for(close_c = 0; close_c !=n;++close_c)
    {
	free(closed[close_c]);
    }
    
    free(closed);
    close_heap(open);
    //start fix for the implementation of points, see earlier comment. I'm too lazy to refactor the code
    ret.x--;
    ret.y--;
    return ret;
}

