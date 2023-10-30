#include <fibheap.h>

fibheap* fibheap_insert(fibheap* heap, int key)
{
    fibheap_node* node = malloc(sizeof node);
    node->key = key;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;

    heap->min = fibheap_add_node_to_root_list(node, heap->min);
    if (heap->min == NULL)
        heap->min = node;
    if (heap->min != NULL)
        if (node->key < heap->min->key)
            heap->min = node;
    heap->nnodes++;
    return heap;
}

fibheap_node* fibheap_add_node_to_root_list(fibheap_node* node, fibheap_node* h)
{
    if(h == NULL)
        return NULL;
    
    if(h->left == h)
    {
        h->left = node;
        h->right = node;
        node->right = h;
        node->left = h;
    }
    else
    {
        fibheap_node* lnode = h->left;
        h->left = node;
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
    fibheap* heap = malloc(sizeof heap);
    heap->min = heap1->min;
    
}