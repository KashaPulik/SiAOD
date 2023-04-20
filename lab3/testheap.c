#include "./minheap.h"

int main()
{
    int* indexes = malloc(100);
    struct heap* h;
    struct heapnode node;
    h = heap_create(32);
    heap_insert(h, 9, 9, &indexes);
    heap_insert(h, 7, 7, &indexes);
    heap_insert(h, 4, 4, &indexes);
    heap_insert(h, 6, 6, &indexes);

    heap_decrease_key(h, 4, 1, &indexes);
    node = heap_extract_min(h, &indexes);
    printf("Item : key = % d; value = %d\n", node.key, node.value);
    node = heap_extract_min(h, &indexes);
    printf("Item : key = % d; value = %d\n", node.key, node.value);
    node = heap_extract_min(h, &indexes);
    printf("Item : key = % d; value = %d\n", node.key, node.value);
    node = heap_extract_min(h, &indexes);
    printf("Item : key = % d; value = %d\n", node.key, node.value);

    heap_free(h);
    free(indexes);
    return 0;
}