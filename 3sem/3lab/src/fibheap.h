#include <stdbool.h>
#include <stdlib.h>

typedef struct fibheap_node {
    int key;
    struct fibheap* parent;
    struct fibheap* child;
    struct fibheap* left;
    struct fibheap* right;
    int degree;
    bool mark;
} fibheap_node;

typedef struct fibheap {
    fibheap_node* min;
    int nnodes;
} fibheap;

fibheap* fibheap_insert(fibheap* heap, int key);
fibheap_node* fibheap_add_node_to_root_list(fibheap_node* node, fibheap_node* h);
fibheap_node* fibheap_min(fibheap* heap);