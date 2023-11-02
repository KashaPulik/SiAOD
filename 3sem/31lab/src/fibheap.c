#include "fibheap.h"

fibheap* make_fibheap()
{
    fibheap* heap = malloc(sizeof *heap);
    heap->nnodes = 0;
    heap->min = NULL;
    return heap;
}

void fibheap_insert(fibheap* heap, int key)
{
    fibheap_node* node = malloc(sizeof(fibheap_node));
    node->key = key;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    fibheap_add_node_to_root_list(node, heap->min);
    if (heap->min == NULL || node->key < heap->min->key)
        heap->min = node;
    heap->nnodes++;
}

void fibheap_add_node_to_root_list(fibheap_node* node, fibheap_node* h)
{
    if (h == NULL)
        return;
    h->left->right = node;
    node->right = h;
    node->left = h->left;
    h->left = node;
}

void fibheap_remove_node_from_root_list(fibheap_node* z)
{
    z->left->right = z->right;
    z->right->left = z->left;
}

fibheap* fibheap_union(fibheap* heap1, fibheap* heap2)
{
    fibheap* heap = make_fibheap();
    heap->min = heap1->min;
    fibheap_link_lists(heap->min, heap2->min);
    if (heap1->min == NULL
        || (heap2->min != NULL && heap2->min->key < heap->min->key))
        heap->min = heap2->min;
    heap->nnodes = heap1->nnodes + heap2->nnodes;
    free(heap1);
    free(heap2);
    return heap;
}

void fibheap_link_lists(fibheap_node* heap1, fibheap_node* heap2)
{
    if (heap1 == NULL || heap2 == NULL)
        return;
    fibheap_node* temp1 = heap1->right;
    fibheap_node* temp2 = heap2->left;
    heap1->right->left = heap2->left;
    heap1->right = heap2;
    heap2->left = heap1;
    temp2->right = temp1;
}

fibheap_node* fibheap_delete_min(fibheap* heap)
{
    fibheap_node *z = heap->min, *x = NULL, *w = heap->min;
    if (z == NULL)
        return NULL;
    if (z->child != NULL) {
        x = z->child;
        do {
            w = x->right;
            fibheap_add_node_to_root_list(x, heap->min);
            if (x->key < heap->min->key)
                heap->min = x;
            x->parent = NULL;
            x = w;
        } while (w != z->child);
    }

    fibheap_remove_node_from_root_list(z);
    heap->min = z->right;

    if (z == z->right && z->child == NULL)
        heap->min = NULL;
    else {
        heap->min = z->right;
        fibheap_consolidate(heap);
    }
    heap->nnodes--;
    return z;
}

void fibheap_consolidate(fibheap* heap)
{
    int degree = D(heap->nnodes), d;
    fibheap_node* A[degree];
    fibheap_node* w = heap->min;
    for (int i = 0; i < degree; i++)
        A[i] = NULL;

    fibheap_node *x = NULL, *y = NULL;

    do {
        x = w;
        d = x->degree;
        while (A[d] != NULL) {
            y = A[d];
            if (x->key > y->key)
                fibheap_swap(&x, &y);
            if (y == heap->min)
                heap->min = x;
            fibheap_link(heap, y, x);
            if (y->right == x)
                heap->min = x;
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        w = w->right;
    } while (w != heap->min);

    heap->min = NULL;
    for (int i = 0; i < degree; i++) {
        if (A[i] != NULL) {
            A[i]->left = A[i];
            A[i]->right = A[i];
            if (heap->min == NULL) {
                heap->min = A[i];
            } else {
                fibheap_add_node_to_root_list(A[i], heap->min);
                if (A[i]->key < heap->min->key)
                    heap->min = A[i];
            }
            if (heap->min == NULL || A[i]->key < heap->min->key)
                heap->min = A[i];
        }
    }
}

int D(int n)
{
    int count = 0;
    while (n > 0) {
        n /= 2;
        count++;
    }
    return count;
}

void fibheap_swap(fibheap_node** x, fibheap_node** y)
{
    fibheap_node* z = *x;
    *x = *y;
    *y = z;
}

void fibheap_link(fibheap* heap, fibheap_node* y, fibheap_node* x)
{
    fibheap_remove_node_from_root_list(y);

    if (x->right == x)
        heap->min = x;

    y->left = y;
    y->right = y;
    y->parent = x;

    if (x->child == NULL)
        x->child = y;

    fibheap_add_node_to_root_list(y, x->child);

    if (y->key < x->child->key)
        x->child = y;

    (x->degree)++;
}

void fibheap_decrease_key(fibheap* heap, fibheap_node* x, int newkey)
{
    if (newkey > x->key)
        return;
    x->key = newkey;
    fibheap_node* y = x->parent;
    if (y != NULL && x->key < y->key) {
        fibheap_cut(heap, x, y);
        fibheap_cascading_cut(heap, y);
    }
    if (x->key < heap->min->key)
        heap->min = x;
}

void fibheap_cut(fibheap* heap, fibheap_node* x, fibheap_node* y)
{
    fibheap_remove_node_from_root_list(x);
    (y->degree)--;
    fibheap_add_node_to_root_list(x, heap->min);
    x->parent = NULL;
    x->mark = false;
}

void fibheap_cascading_cut(fibheap* heap, fibheap_node* y)
{
    fibheap_node* z = y->parent;
    if (z == NULL)
        return;
    if (y->mark == false)
        y->mark = true;
    else {
        fibheap_cut(heap, y, z);
        fibheap_cascading_cut(heap, z);
    }
}

void fibheap_delete(fibheap* heap, fibheap_node* x)
{
    fibheap_decrease_key(heap, x, -1);
    fibheap_delete_min(heap);
}

void printFibonacciHeapRecursive(fibheap_node* node, int depth)
{
    if (node == NULL) {
        return;
    }

    printf("%d", node->key);
    if (node->parent != NULL) {
        printf(" (Parent: %d)", node->parent->key);
    }
    printf("\n");

    fibheap_node* child = node->child;
    if (child != NULL) {
        printf("  Children of %d:\n", node->key);
        do {
            for (int i = 0; i < depth; i++) {
                printf("  ");
            }
            printFibonacciHeapRecursive(child, depth + 1);
            child = child->right;
        } while (child != node->child);
    }
}

// Функция для вывода всей Фибоначчиевой кучи
void fibheap_print(fibheap_node* min)
{
    if (min == NULL) {
        printf("The Fibonacci heap is empty.\n");
        return;
    }

    printf("Fibonacci Heap with Parent-Child Relationships:\n");
    fibheap_node* current = min;
    do {
        printFibonacciHeapRecursive(current, 0);
        current = current->right;
    } while (current != min);
}
