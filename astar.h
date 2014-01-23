#include "graphics.h"

struct Node
{
    struct point_t p;
    int f, h;
    struct Node * parent;
};
typedef struct Node Node;

struct Node_heap
{
    Node** heap;
    int size;
};
typedef struct Node_heap Node_heap;

Node* init_Node();
Node* init_NodeP(point_t p);
Node* init_NodeA(point_t p, int f, int h, Node* parent);

Node_heap* init_Node_heap();
void insert(Node *x, Node_heap* heap);
Node* pop(Node_heap *heap);
Node* getMin(Node_heap *heap);
