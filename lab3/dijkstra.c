#include "./graph.h"
#include "./minheap.h"

void shortest_path_dijkstra(struct graph* g, int src, int** D, int** prev)
{
    int* temp_D = malloc(sizeof(int) * g->nvertices);
    int* temp_prev = malloc(sizeof(int) * g->nvertices);
    int* indexes = malloc(sizeof(int) * g->nvertices);

    src--;
    struct heapnode node;
    Heap* Q = heap_create(g->nvertices);
    int i, j;
    for (i = 0; i < g->nvertices; i++) {
        if (i == src)
            continue;
        temp_D[i] = 1000000000;
        temp_prev[i] = -1;
        heap_insert(Q, temp_D[i], i, &indexes);
    }
    temp_D[src] = 0;
    temp_prev[src] = -1;
    heap_insert(Q, temp_D[src], src, &indexes);
    for (i = 0; i < g->nvertices; i++) {
        node = heap_extract_min(Q, &indexes);
        g->visited[node.value] = 1;
        for (j = 0; j < g->nvertices; j++) {
            if (graph_get_edge(g, node.value + 1, j + 1) == 0)
                continue;
            if (g->visited[j] == 1)
                continue;
            if ((temp_D[node.value] + graph_get_edge(g, node.value + 1, j + 1))
                < temp_D[j]) {
                temp_D[j] = temp_D[node.value]
                        + graph_get_edge(g, node.value + 1, j + 1);
                heap_decrease_key(Q, indexes[j], temp_D[j], &indexes);
                temp_prev[j] = node.value;
            }
        }
    }
    for (i = 0; i < g->nvertices; i++)
        g->visited[i] = 0;
    *D = temp_D;
    *prev = temp_prev;
    free(indexes);
    heap_free(Q);
}

int search_shortest_path(struct graph* g, int src, int dst, int** path)
{
    int* D = NULL;
    int* prev = NULL;
    shortest_path_dijkstra(g, src, &D, &prev);
    int i = dst - 1;
    int pathlen = 1;
    while (i != (src - 1)) {
        pathlen++;
        i = prev[i];
    }
    int j = 1;
    i = dst - 1;
    *path = malloc(sizeof(int) * pathlen);
    while (i != (src - 1)) {
        (*path)[pathlen - j] = i + 1;
        j++;
        i = prev[i];
    }
    (*path)[pathlen - j] = src;
    free(D);
    free(prev);
    return pathlen;
}

void print_shortest_path(struct graph* g, int src, int dest)
{
    int* path = NULL;
    int pathlen = search_shortest_path(g, src, dest, &path);
    print_path(pathlen, path);
    free(path);
}