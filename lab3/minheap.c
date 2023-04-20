#include "./minheap.h"

Heap* heap_create(int maxsize)
{
    Heap* h;
    h = malloc(sizeof(*h));
    if (h != NULL) {
        h->maxsize = maxsize;
        h->nnodes = 0;
        h->nodes = malloc(sizeof(*h->nodes) * (maxsize + 1));
        if (h->nodes == NULL) {
            free(h);
            return NULL;
        }
    }
    return h;
}

void heap_free(Heap* h)
{
    free(h->nodes);
    free(h);
}

void heap_swap(struct heapnode* a, struct heapnode* b)
{
    struct heapnode temp = *a;
    *a = *b;
    *b = temp;
}

struct heapnode* heap_min(Heap* h)
{
    if (h->nnodes == 0)
        return NULL;
    return &h->nodes[1];
}

int heap_insert(Heap* h, int key, int value, int** indexes)
{
    if (h->nnodes >= h->maxsize)
        return -1;

    int tmp;
    h->nnodes++;
    h->nodes[h->nnodes].key = key;
    h->nodes[h->nnodes].value = value;

    (*indexes)[value] = h->nnodes;

    for (int i = h->nnodes; (i > 1) && (h->nodes[i].key < h->nodes[i / 2].key);
         i = i / 2) {
        tmp = (*indexes)[h->nodes[i].value];
        (*indexes)[h->nodes[i].value] = (*indexes)[h->nodes[i / 2].value];
        (*indexes)[h->nodes[i / 2].value] = tmp;
        heap_swap(&h->nodes[i], &h->nodes[i / 2]);
    }
    return 0;
}

int* heap_heapify(Heap* h, int index, int** indexes)
{
    int tmp;
    while (1) {
        int left = 2 * index;
        int right = 2 * index + 1;
        int minimal = index;
        if ((left <= h->nnodes) && (h->nodes[left].key < h->nodes[minimal].key))
            minimal = left;
        if ((right <= h->nnodes)
            && (h->nodes[right].key < h->nodes[minimal].key))
            minimal = right;
        if (minimal == index)
            break;
        tmp = (*indexes)[h->nodes[index].value];
        (*indexes)[h->nodes[index].value] = (*indexes)[h->nodes[minimal].value];
        (*indexes)[h->nodes[minimal].value] = tmp;
        heap_swap(&h->nodes[index], &h->nodes[minimal]);
        index = minimal;
    }
    return *indexes;
}

struct heapnode heap_extract_min(Heap* h, int** indexes)
{
    if (h->nnodes == 0)
        return (struct heapnode){0, 0};

    struct heapnode minnode = h->nodes[1];
    h->nodes[1] = h->nodes[h->nnodes--];
    *indexes = heap_heapify(h, 1, indexes);

    return minnode;
}

int heap_decrease_key(Heap* h, int index, int newkey, int** indexes)
{
    if (h->nodes[index].key <= newkey)
        return -1;

    int tmp;
    h->nodes[index].key = newkey;
    while (index > 1 && h->nodes[index].key < h->nodes[index / 2].key) {
        tmp = (*indexes)[h->nodes[index].value];
        (*indexes)[h->nodes[index].value]
                = (*indexes)[h->nodes[index / 2].value];
        (*indexes)[h->nodes[index / 2].value] = tmp;
        heap_swap(&h->nodes[index], &h->nodes[index / 2]);
        index /= 2;
    }
    return index;
}