#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct fibheap_node {
    int key;
    struct fibheap_node* parent;
    struct fibheap_node* child;
    struct fibheap_node* left;
    struct fibheap_node* right;
    int degree;
    bool mark;
} fibheap_node;

typedef struct fibheap {
    fibheap_node* min;
    int nnodes;
} fibheap;

fibheap* fibheap_insert(fibheap* heap, int key);
fibheap* fibheap_add_node_to_root_list(fibheap_node* node, fibheap* h);
fibheap_node* fibheap_min(fibheap* heap);
fibheap* fibheap_union(fibheap* heap1, fibheap* heap2);
fibheap_node* fibheap_link_lists(fibheap_node* heap1, fibheap_node* heap2);
fibheap_node* fibheap_delete_min(fibheap* heap);
fibheap* fibheap_remove_node_from_root_list(fibheap_node* z, fibheap* heap);
fibheap* fibheap_consolidate(fibheap* heap);
void fibheap_swap(fibheap_node** x, fibheap_node** y);
int D(int n);
fibheap* fibheap_link(fibheap* heap, fibheap_node* x, fibheap_node* y);