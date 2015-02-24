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

//inserts a node into the node heap so that the heap remains ordered
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

//frees the heap
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

//adds all of the current node's neighbors
int add_neighs(point_t home, point_t* neigh, char **map)
{
    int n = 0;
    if(map[home.y+1][home.x] != 'x' )
    {
	neigh[n++] = (point_t){home.x,home.y+1};
    }
    if(map[home.y][home.x+1] != 'x' )
    {
	neigh[n++] = (point_t){home.x+1,home.y};
    }
    if(map[home.y-1][home.x] != 'x' )
    {
	neigh[n++] = (point_t){home.x,home.y-1};
    }
    if(map[home.y][home.x-1] != 'x' )
    {
	neigh[n++] = (point_t){home.x-1,home.y};
    }

    return n;
}

int calcH(point_t curr, point_t end)
{
    return abs(end.x - curr.x) + abs(end.y - curr.y);
}

int isIn(Node** in, int size, point_t p)
{
    int n;
    for(n = 0;n<= size; ++n)
    {
	//if it doesnt go past size
	if(n!=0)
	if(in[n] != NULL && p_equals(in[n]->p,p))
	    return 1;
    }
    return 0;
}

point_t astar(point_t begin, point_t end, char** map)
{
    //to fix transition mistakes. map is formatted with 1,1 being the first open spot for logistics, but entity point class has 0,0 being the first as per convention
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
	Node* current = pop(open);
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
		Node* neigh = init_NodeA(neighs[c],cost,calcH(neighs[c],end),current);
		insert(neigh,open);
	    }
	}
	free(neighs);
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

    ret.x--;
    ret.y--;
    return ret;
}

