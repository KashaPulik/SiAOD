#include "./graph.h"
#include "./minheap.h"

void shortest_path_dijkstra(struct graph* g, int src, int* D, int* prev)
{
    int* indexes = malloc(sizeof(int) * g->nvertices);
    src--;
    struct heapnode node;
    Heap* Q = heap_create(g->nvertices);
    int i, j;
    for (i = 0; i < g->nvertices; i++) {
        if (i == src)
            continue;
        D[i] = 1000000000;
        prev[i] = -1;
        heap_insert(Q, D[i], i, &indexes);
    }
    D[src] = 0;
    prev[src] = -1;
    heap_insert(Q, D[src], src, &indexes);
    for (i = 0; i < g->nvertices; i++) {
        // printf("%d %d %d %d %d %d %d %d %d \n", indexes[0], indexes[1], indexes[2], indexes[3], indexes[4], indexes[5], indexes[6], indexes[7], indexes[8]);
        node = heap_extract_min(Q, &indexes);
        g->visited[node.value] = 1;
        for (j = 0; j < g->nvertices; j++) {
            if (graph_get_edge(g, node.value + 1, j + 1) == 0)
                continue;
            if (g->visited[j] == 1)
                continue;
            if ((D[node.value] + graph_get_edge(g, node.value + 1, j + 1)) < D[j]) {
                D[j] = D[node.value] + graph_get_edge(g, node.value + 1, j + 1);
                heap_decrease_key(Q, indexes[j], D[j], &indexes);
                prev[j] = node.value;
            }
        }
    }
    free(indexes);
    heap_free(Q);
}

int search_shortest_path(struct graph* g, int src, int dst, int** path)
{
    int* D = malloc(g->nvertices * sizeof(int));
    int* prev = malloc(g->nvertices * sizeof(int));
    shortest_path_dijkstra(g, src, D, prev);
    src--;
    dst--;
    int i = dst;
    int pathlen = 1;
    while(i != src) {
        pathlen++;
        i = prev[i];
    }
    int j = 1;
    i = dst;
    *path = malloc(pathlen * sizeof(int));
    while (i != src) {
        (*path)[pathlen - j] = i + 1;
        j++;
        i = prev[i];
    }
    (*path)[pathlen - j] = i + 1;
    free(D);
    free(prev);
    return pathlen;
}