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
fibheap *make_fibheap();
fibheap_node* make_fibheap_node(int key);
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
fibheap_node* fibheap_add_node_to_sibling_list(fibheap_node* y, fibheap_node* x);
fibheap* fibheap_link(fibheap* heap, fibheap_node* x, fibheap_node* y);

fibheap *make_fibheap()
{
  fibheap *heap = malloc(sizeof *heap);
  heap->nnodes = 0;
  heap->min = NULL;
  return heap;
}

fibheap_node* make_fibheap_node(int key)
{
    fibheap_node* node = malloc(sizeof *node);
    node->key = key;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

fibheap* fibheap_insert(fibheap* heap, int key)
{
    fibheap_node* node = make_fibheap_node(key);

    heap = fibheap_add_node_to_root_list(node, heap);
    if (heap->min == NULL || node->key < heap->min->key)
        heap->min = node;
    heap->nnodes++;
    return heap;
}

fibheap* fibheap_add_node_to_root_list(fibheap_node* node, fibheap* h)
{
    if (h == NULL)
        return NULL;

    if (h->min->left == h) {
        h->min->left = node;
        h->min->right = node;
        node->right = h;
        node->left = h;
    } else {
        fibheap_node* lnode = h->min->left;
        h->min->left = node;
        node->right = h;
        node->left = lnode;
        lnode->right = node;
    }
    return h;
}

fibheap_node* fibheap_min(fibheap* heap)
{
    return heap->min;
}

fibheap* fibheap_union(fibheap* heap1, fibheap* heap2)
{
    fibheap* heap = make_fibheap();
    heap->min = heap1->min;
    heap1->min = fibheap_link_lists(heap1->min, heap2->min);
    if (heap1->min == NULL
        || (heap2->min != NULL && heap2->min->key < heap->min->key))
        heap->min = heap2->min;
    heap->nnodes = heap1->nnodes + heap2->nnodes;
    free(heap1);
    free(heap2);
    return heap;
}

fibheap_node* fibheap_link_lists(fibheap_node* heap1, fibheap_node* heap2)
{
    if (heap1 == NULL || heap2 == NULL)
        return NULL;

    fibheap_node *left1 = NULL, *left2 = NULL;

    left1 = heap1->left;
    left2 = heap2->left;
    left1->right = heap2;
    heap2->left = left1;
    heap1->left = left2;
    left2->right = heap1;
    return heap1;
}

fibheap_node* fibheap_delete_min(fibheap* heap)
{
    fibheap_node* z = heap->min;
    if (z == NULL)
        return NULL;
    fibheap_node* x = z->child;
    for (int i = 0; i < z->degree; i++) {
        heap = fibheap_add_node_to_root_list(x, heap);
        x->parent = NULL;
        x = x->right;
    }
    heap = fibheap_remove_node_from_root_list(z, heap);
    if (z == z->right)
        heap->min = NULL;
    else {
        heap->min = z->right;
        heap = fibheap_consolidate(heap);
    }
    heap->nnodes = heap->nnodes - 1;
    return z;
}

fibheap* fibheap_remove_node_from_root_list(fibheap_node* z, fibheap* heap)
{
    if (z == NULL || heap == NULL)
        return NULL;
    fibheap_node* left = z->left;
    fibheap_node* right = z->right;
    left->right = right;
    right->left = left;
    return heap;
}

fibheap* fibheap_consolidate(fibheap* heap)
{
    int n_root_nodes = D(heap->nnodes);
    fibheap_node* A[n_root_nodes];
    for (int i = 0; i < n_root_nodes; i++) {
        A[i] = NULL;
    }
    fibheap_node *y = NULL, *x = NULL, *w = heap->min;
    int d;
    for (int i = 0; i < n_root_nodes; i++) {
        x = w;
        d = x->degree;
        while (A[d] != NULL) {
            y = A[d];
            if (x->key > y->key)
                fibheap_swap(&x, &y);
            heap = fibheap_link(heap, x, y);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }
    heap->min = NULL;
    for (int i = 0; i < n_root_nodes; i++) {
        if (A[i] != NULL) {
            heap = fibheap_add_node_to_root_list(A[i], heap);
            if (heap->min == NULL || A[i]->key < heap->min->key)
                heap->min = A[i];
        }
    }
    return heap;
}

void fibheap_swap(fibheap_node** x, fibheap_node** y)
{
    fibheap_node* z = malloc(sizeof *z);
    z->child = (*x)->child;
    z->degree = (*x)->degree;
    z->key = (*x)->key;
    z->left = (*x)->left;
    z->mark = (*x)->mark;
    z->parent = (*x)->parent;
    z->right = (*x)->right;

    (*x)->child = (*y)->child;
    (*x)->degree = (*y)->degree;
    (*x)->key = (*y)->key;
    (*x)->left = (*y)->left;
    (*x)->mark = (*y)->mark;
    (*x)->parent = (*y)->parent;
    (*x)->right = (*y)->right;

    (*y)->child = z->child;
    (*y)->degree = z->degree;
    (*y)->key = z->key;
    (*y)->left = z->left;
    (*y)->mark = z->mark;
    (*y)->parent = z->parent;
    (*y)->right = z->right;

    free(z);
}

int D(int n)
{
    return floor(log2(n));
}

fibheap_node* fibheap_add_node_to_sibling_list(fibheap_node* y, fibheap_node* x)
{
    y->right = x;
    y->left = x->left;
    x->left->right = y;
    x->left = y;
    x = y;
    return x;
}

fibheap* fibheap_link(fibheap* heap, fibheap_node* x, fibheap_node* y)
{
    x->degree++;
    heap = fibheap_remove_node_from_root_list(y, heap);
    y->parent = x;
    x->child = fibheap_add_node_to_sibling_list(y, x->child); // Вот это неправильно
    y->mark = false;
    return heap;
}

