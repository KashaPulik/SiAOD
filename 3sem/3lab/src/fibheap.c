#include "fibheap.h"
#include <math.h>

fibheap* make_fibheap()
{
    fibheap* heap = malloc(sizeof *heap);
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

    fibheap_add_node_to_root_list(node, heap->min);
    if (heap->min == NULL || node->key < heap->min->key)
        heap->min = node;
    heap->nnodes++;
    return heap;
}

void fibheap_add_node_to_root_list(fibheap_node* node, fibheap_node* h)
{
    if (h == NULL)
        return;

    if (h->left == h) {
        h->left = node;
        h->right = node;
        node->right = h;
        node->left = h;
    } else {
        node->left = h->left;
        node->left->right = node;
        h->left = node;
        node->right = h;
    }
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

    if (z->child) {
        fibheap_node* x = z->child;
        int n = 1;
        x = x->right;
        while (x != z->child) {
            x = x->right;
            n++;
        }
        for (int i = 0; i < n; i++) {
            fibheap_add_node_to_root_list(x, heap->min);
            x->parent = NULL;
            x = x->left;
        }
    }

    fibheap_remove_node_from_root_list(z);

    if (z == z->right)
        heap->min = NULL;
    else {
        heap->min = z->right;
        heap = fibheap_consolidate(heap);
    }

    heap->nnodes--;

    // free(z);

    return z;
}

void fibheap_remove_node_from_root_list(fibheap_node* z)
{
    z->right->left = z->left;
    z->left->right = z->right;
}

fibheap* fibheap_consolidate(fibheap* heap)
{
    int degree = D(heap->nnodes), n = 0;
    fibheap_node** arr_Node = malloc(sizeof(fibheap_node) * degree);
    fibheap_node* node = NULL;

    for (int i = 0; i <= degree; i++) {
        arr_Node[i] = NULL;
    }

    while (node != heap->min) {
        if (node == NULL)
            node = heap->min;
        n++;
        node = node->right;
    }

    for (int i = 0; i < n; i++) {
        int n_degree = node->degree;
        while (arr_Node[n_degree] != NULL) {
            if (arr_Node[n_degree]->key < node->key) {
                if (arr_Node[n_degree]->child != NULL) {
                    fibheap_link(arr_Node[n_degree], node);
                } else {
                    arr_Node[n_degree]->child = node;
                    fibheap_remove_node_from_root_list(node);
                    node->left = node;
                    node->right = node;
                    arr_Node[n_degree]->degree++;
                    node->parent = arr_Node[n_degree];
                }
                node = arr_Node[n_degree];
            } else {
                if (node->child != NULL) {
                    fibheap_link(node, arr_Node[n_degree]);
                } else {
                    node->child = arr_Node[n_degree];
                    fibheap_remove_node_from_root_list(arr_Node[n_degree]);
                    arr_Node[n_degree]->left = arr_Node[n_degree];
                    arr_Node[n_degree]->right = arr_Node[n_degree];
                    node->degree++;
                    arr_Node[n_degree]->parent = node;
                }
            }
            arr_Node[n_degree] = NULL;
            n_degree++;
        }
        arr_Node[n_degree] = node;
        node = node->right;
    }

    for (int i = 0; i <= degree; i++) {
        if (arr_Node[i] != NULL) {
            if (heap->min == NULL || heap->min->key > arr_Node[i]->key) {
                heap->min = arr_Node[i];
            }
        }
    }

    return heap;
}

void fibheap_swap(fibheap_node** x, fibheap_node** y)
{
    fibheap_node* z = *x;
    *x = *y;
    *y = z;
}

int D(int n)
{
    return floor(log(n));
}

void fibheap_link(fibheap_node* x, fibheap_node* y)
{
    x->degree++;
    fibheap_remove_node_from_root_list(y);
    y->parent = x;
    fibheap_add_node_to_root_list(y, x->child);
    y->mark = false;
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
    y->degree--;
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

void fibheap_delete_node(fibheap* heap, fibheap_node* x)
{
    fibheap_decrease_key(heap, x, -1);
    fibheap_delete_min(heap);
}

void fibheap_delete_heap(fibheap* heap)
{
    while (heap->nnodes)
        fibheap_delete_min(heap);

    free(heap);
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
