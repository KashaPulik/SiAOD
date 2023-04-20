#include "./minheap.h"

int main()
{
    struct heap* h;
    struct heapnode node;
    h = heap_create(32);
    heap_insert(h, 9, 9);
    heap_insert(h, 7, 7);
    heap_insert(h, 4, 4);

    node = heap_extract_min(h);
    printf("Item : % d\n", node.key);
    node = heap_extract_min(h);
    printf("Item : % d\n", node.key);
    node = heap_extract_min(h);
    printf("Item : % d\n", node.key);

    int i = heap_increase_key(h, 4, 14);
    heap_free(h);
    return 0;
}