#define U 1
#define R 2
#define D 3
#define L 4

typedef struct Node Node;
typedef struct Node_heap Node_heap;
typedef struct Point Point;

struct Point
{
    int x, y;
};

struct Node
{
    Point p;
    int f, h;
    Node * parent;
};

struct Node_heap
{
    Node** heap;
    int size;
};

Point init_Point(int x, int y);

Node* init_Node();
Node* init_NodeP(Point p);
Node* init_NodeA(Point p, int f, int h, Node* parent);

Node_heap* init_Node_heap();
void insert(Node *x, Node_heap* heap);
Node* pop(Node_heap *heap);
Node* getMin(Node_heap *heap);

Point astar(Point begin, Point end, char** map);
