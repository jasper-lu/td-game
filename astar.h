#define U 1
#define R 2
#define D 3
#define L 4

typedef struct Node Node;
typedef struct Node_heap Node_heap;

typedef struct
{
    int x, y;
}Point;

struct Node
{
    Point p;
    int f, h;
    Node * parent;
};

Node* init_Node()
{
    Node* node;
    node = malloc(sizeof(Node));
    node->p.x=0;node->p.y=0;node->f=0;node->h=0;node->parent = NULL;
    return node;
}

Node* init_NodeP(Point p)
{
    Node *node;
    node = malloc(sizeof(Node));
    node->p = p;
    node->f = 0;
    node->h = 0;
    node->parent = NULL;
}

Node* init_NodeA(Point p, int f, int h, Node* parent)
{
    Node* node;
    node = malloc(sizeof(Node));
    node->p = p; node->f = f; node->h = h; node->parent = parent;
}

Point init_Point(int x, int y)
{
    Point ret;
    ret.x = x; ret.y = y;
    return ret;
}

struct Node_heap
{
    Node** heap;
    int size;
};

Node_heap* init_Node_heap()
{
    Node_heap *heap = malloc(sizeof(Node_heap)); 
    heap->heap = malloc(sizeof(Node) * 1600);
    heap->size = 0;
    return heap;
}

int compare(Node* lhs, Node * rhs)
{
    return (lhs->f + lhs->h) - (rhs->f + rhs->h);
}
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

int close(Node_heap *heap) { 
    int i;
    for(i = 0; i <= heap->size; ++i)
	free(heap->heap[i]);
    free(heap->heap);
    free(heap);
}

int p_equals(Point lhs, Point rhs)
{
    if(lhs.x == rhs.x && lhs.x == rhs.x)
	return 1;
    else
	return 0;
}

int add_neighs(Point home, Point* neigh, char **map)
{
    int n = 0;
    if(map[home.y+1][home.x] == ' ')
	neigh[n++] = init_Point(home.x+1,home.y);
    if(map[home.y][home.x+1] == ' ')
	neigh[n++] = init_Point(home.x,home.y+1);
    if(map[home.y-1][home.x] == ' ')
	neigh[n++] = init_Point(home.x-1,home.y);
    if(map[home.y][home.x-1] == ' ')
	neigh[n++] = init_Point(home.x,home.y-1);

    printf("this round: %d", n);
    return n;
}

int calcH(Point curr, Point end)
{
    return (end.x - curr.x) + (end.y - curr.y);
}

int isIn(Node** in, int size, Point p)
{
    int n;
    for(n = 0;n<= size; ++n)
    {
	//if it doesnt go past size
	printf("%d -- size: %d\n", n, size);
	if(in[n] != NULL && p_equals(in[n]->p,p))
	    return 1;
    }
    printf("yolo\n");
    return 0;
}

int astar(Point begin, Point end, char** map)
{
    Node *start = init_NodeA(begin, 0, calcH(begin,end),NULL); 
    Node_heap *open = init_Node_heap();
    insert(start, open);
    Node** closed = malloc(sizeof(Node) * 1600);
    int n =0;
    while(!(p_equals(getMin(open)->p,end)))
    {
	Node* current = pop(open);
	closed[n] = current;
	++n;
	Point* neighs = malloc(sizeof(Point) * 4);
	int neigh_size = add_neighs(current->p,neighs,map);
	int c;
    printf("%d,%d\n",getMin(open)->p.x,getMin(open)->p.y);

	int cost = current->f + 1;

	for(c = 0; c != neigh_size; ++c)
	{
//	    if(!(isIn(open->heap, open->size,neighs[c])) && !(isIn(closed,n-1,neighs[c])))
		if(!(isIn(open->heap, open->size, neighs[c])))
	    {
		printf("is the error here?\n");
		Node* neigh = init_NodeA(neighs[c],cost,calcH(neighs[c],end),current);
		insert(neigh,open);
	    }
	    printf("next one");
	}
	free(neighs);
    }

    printf("Final: %d,%d\n",getMin(open)->p.x,getMin(open)->p.y);

    int close_c;
    for(close_c = 0; close_c !=n;++close_c)
    {
	free(closed[close_c]);
    }
    free(closed);
    close(open);
}
