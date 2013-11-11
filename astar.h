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

void insert(Node *x, Node_heap* heap)
{
    heap->heap[heap->size] = x;
}

Node* getMin(Node_heap* heap)
{
    return heap->heap[0];
}

