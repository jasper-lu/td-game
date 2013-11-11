typedef struct Node Node;
typedef struct Node_heap Node_heap;

struct Node
{
    int x, y, f, h;
    Node * parent;
};

Node* init_Node()
{
    Node* node;
    node = malloc(sizeof(Node));
    node->x=0;node->y=0;node->f=0;node->h=0;node->parent = NULL;
}

typedef struct
{
    Node_heap* open;
    Node* closed;
}Node_pQueue;

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

int compare(Node* lhs, Node * rh)
{
    return (lhs->f + lhs->h) - (rhs->f + rhs->h);
}

void insert(Node *x, Node_heap* heap)
{
    int n = ++size;
    for(; n > 0 && compare(x, heap.heap[(n/2) -1]) < 0; n=(n/2)-1)
    {
	Node *temp = heap.heap[(n/2)-1];
    }
    heap.heap[n] = x;    
}

Node* getMin(Node_heap* heap)
{
    return heap->heap[0];
}
