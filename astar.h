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
