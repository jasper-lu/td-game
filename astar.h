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
    printf("yo\n");
        heap->size++;
        heap->heap[heap->size] = x; /*Insert in the last place*/
        /*Adjust its position*/
        int now = heap->size;
	while(now > 1 && compare(heap->heap[now/2], x) > 0)
        {
                heap[now] = heap[now/2];
                now /= 2;
        }
        heap->heap[now] = x;
}
/*
void insert(Node *x, Node_heap* heap)
{
    printf("in\n");
    int n = (heap->size)++;
    for(; n > 1 && compare(x, heap->heap[(n/2) -1]) < 0; n=(n/2)-1)
    {
	heap->heap[(n/2)-1] = heap->heap[n];
    }
    if(n == 1 && compare(x,heap->heap[0]) < 0)
    {
	heap->heap[1] = heap->heap[0];
	n = 0;
    }
    heap->heap[n] = x;    
}

Node* getMin(Node_heap* heap)
{
    Node* ret = heap->heap[0];
    return ret;
}
*/

void swap(Node **a, Node **b)
{
    Node **temp = a;
    a = b;
    b = temp;
}

Node* pop(Node_heap * heap)
{
        /* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased. 
           Now heap[1] has to be filled. We put the last element in its place and see if it fits.
           If it does not fit, take minimum element among both its children and replaces parent with it.
           Again See if the last element fits in that place.*/
        Node* minElement;
	Node* lastElement;
	int now, child;
        minElement = heap->heap[1];
        lastElement = heap->heap[(heap->size)--];
        /* now refers to the index at which we are now */
        for(now = 1; now*2 <= heap->size ;now = child)
        {
                /* child is the index of the element which is minimum among both the children */ 
                /* Indexes of children are i*2 and i*2 + 1*/
                child = now*2;
                /*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one 
                  child */
                if(child != heap->size && compare(heap->heap[child+1],heap->heap[child]) < 0) 
                {
		    printf("first if is fine\n");
                        child++;
                }
                /* To check if the last element fits ot not it suffices to check if the last element
                   is less than the minimum element among both the children*/
		printf("%d\n", lastElement->f);
                if(compare(lastElement,heap->heap[child]) > 0)
                {
		    printf("inside 2nd if\n");
                        heap->heap[now] = heap->heap[child];
                }
                else /* It fits there */
                {
		    printf("can't be here\n");
                        break;
                }
        }
        heap->heap[now] = lastElement;
        return minElement;
}
/*
Node* pop(Node_heap* heap)
{
    Node* ret = heap->heap[0];
    //printf("%d",heap->heap[0]->f);

    printf("before: %d\n",heap->heap[2]->f);
    swap(&heap->heap[0], &heap->heap[heap->size-1]);
    printf("after: %d\n",heap->heap[2]->f);

//    printf("%d, %d before \n",getMin(heap)->f, getMin(heap)->f);
 //   printf("size: %d\n", heap->size);
  //  printf("%d,\n",(heap->heap[0])->f);
    heap->heap[heap->size-1] = NULL;
    int n;
    (heap->size)--;
    for(n = 0; n*2+1 < heap->size;n = 2*n +1)
    {
	printf("|0: %d|\n",heap->heap[0]->f);
	if(compare(heap->heap[(2*n)+1],heap->heap[n]) > 0)
	    swap(&heap->heap[(2*n)+1],&heap->heap[n]);
	else if(n*2 +2 < heap->size && compare(heap->heap[(2*n)+2],heap->heap[n]) >0)
	    swap(&heap->heap[(2*n)+2],&heap->heap[n]);
	else
	    break;
    }
    return ret;
}
*/

