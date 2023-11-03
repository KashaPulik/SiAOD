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
    if (h->left == h) {
        h->left = node;
        h->right = node;
        node->right = h;
        node->left = h;
    } else {
        fibheap_node* lnode = h->left;
        h->left = node;
        node->right = h;
        node->left = lnode;
        lnode->right = node;
    }
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
        } while (x != z->child);
    }

    fibheap_remove_node_from_root_list(z);

    if (z == z->right)
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
    fibheap_node* A[degree + 1];
    for (int i = 0; i <= degree; i++)
        A[i] = NULL;

    fibheap_node *x = heap->min, *y = NULL;

    do {
        d = x->degree;
        while (A[d] != NULL) {
            y = A[d];
            if (x->key > y->key)
                fibheap_swap(&x, &y);
            if (y == heap->min)
                heap->min = x;
            fibheap_link(y, x);
            if (y->right == x)
                heap->min = x;
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        x = x->right;
    } while (x != heap->min);

    heap->min = NULL;
    for (int i = 0; i <= degree; i++) {
        if (A[i] != NULL) {
            A[i]->left = A[i];
            A[i]->right = A[i];
            fibheap_add_node_to_root_list(A[i], heap->min);
            if (heap->min == NULL || A[i]->key < heap->min->key)
                heap->min = A[i];
        }
    }
}

int D(int n)
{
    return floor(log2(n));
}

void fibheap_swap(fibheap_node** x, fibheap_node** y)
{
    fibheap_node* z = *x;
    *x = *y;
    *y = z;
}

void fibheap_link(fibheap_node* y, fibheap_node* x)
{
    fibheap_remove_node_from_root_list(y);

    y->left = y;
    y->right = y;
    y->parent = x;

    fibheap_add_node_to_root_list(y, x->child);
    if (x->child == NULL)
        x->child = y;

    if (y->key < x->child->key)
        x->child = y;

    y->mark = false;

    x->degree++;
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

void fibheap_print_recursive(fibheap_node* node, int depth)
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
            fibheap_print_recursive(child, depth + 1);
            child = child->right;
        } while (child != node->child);
    }
}

// Функция для вывода всей Фибоначчиевой кучи
void fibheap_print(fibheap* heap)
{
    if (heap->min == NULL) {
        printf("The Fibonacci heap is empty.\n");
        return;
    }

    printf("Fibonacci Heap:\n");
    fibheap_node* current = heap->min;
    do {
        fibheap_print_recursive(current, 0);
        current = current->right;
    } while (current != heap->min);
    printf("\n");
}
