#include "./graph.h"
#include "./dijkstra.h"

void graph_clear(struct graph* g)
{
    int i, j;
    for (i = 0; i < g->nvertices; i++) {
        g->visited[i] = 0;
        for (j = 0; j < g->nvertices; j++) {
            g->m[i * g->nvertices + j] = 0;
        }
    }
}

struct graph* graph_create(int nvertices)
{
    struct graph* g;
    g = malloc(sizeof(*g));
    g->nvertices = nvertices;
    g->m = malloc(sizeof(int) * nvertices * nvertices);
    g->visited = malloc(sizeof(int) * nvertices);
    graph_clear(g);
    return g;
}

void graph_free(struct graph* g)
{
    free(g->visited);
    free(g->m);
    free(g);
}

void graph_set_edge(struct graph* g, int i, int j, int w)
{
    g->m[(i - 1) * g->nvertices + j - 1] = w;
    g->m[(j - 1) * g->nvertices + i - 1] = w;
}

int graph_get_edge(struct graph* g, int i, int j)
{
    return g->m[(i - 1) * g->nvertices + j - 1];
}

void graph_dfs(struct graph* g, int v)
{
    int i;
    g->visited[v - 1] = 1;
    printf("Vertex %d\n", v);
    for (i = 0; i < g->nvertices; i++)
        if (g->m[(v - 1) * g->nvertices + i] > 0 && g->visited[i] == 0)
            graph_dfs(g, i + 1);
}

void print_graph(struct graph* g)
{
    int i, j;
    for (i = 0; i < g->nvertices; i++) {
        for (j = 0; j < g->nvertices; j++) {
            if (g->m[i * g->nvertices + j] == 0)
                printf(COLOR_RED "%d  " COLOR_RESET,
                       g->m[i * g->nvertices + j]);
            else
                printf(COLOR_GREEN "%d  " COLOR_RESET,
                       g->m[i * g->nvertices + j]);
        }
        printf("| %d\n", i + 1);
    }
    for (i = 0; i < g->nvertices; i++)
        printf("‾‾‾");
    printf("\n");
    for (i = 0; i < g->nvertices; i++)
        printf("%d  ", i + 1);
    printf("\n");
}

struct graph* make_connected_graph(int nvertices, int weight)
{
    struct graph* g = graph_create(nvertices);
    for (int i = 1; i <= g->nvertices; i++) {
        for (int j = 1; j <= g->nvertices; j++) {
            if (i == j)
                continue;
            graph_set_edge(g, i, j, rand() % weight + 1);
        }
    }
    return g;
}

struct graph* make_lattice_graph(int side_length, int weight)
{
    struct graph* g = graph_create(side_length * side_length);
    for (int i = 1; i < g->nvertices; i++) {
        if (i % side_length != 0)
            graph_set_edge(g, i, i + 1, rand() % weight + 1);
        if ((i - g->nvertices + side_length) < 1)
            graph_set_edge(g, i, i + side_length, rand() % weight + 1);
    }
    return g;
}

void print_pathlens(struct graph* g, int src)
{
    int* D;
    int* prev;
    shortest_path_dijkstra(g, src, &D, &prev);
    for (int i = 0; i < g->nvertices; i++) {
        printf("1 -> %d = %d\n", i + 1, D[i]);
    }
    free(D);
    free(prev);
}

void print_path(int pathlen, int* path)
{
    int i;
    for (i = 0; i < pathlen - 1; i++)
        printf("%d -> ", path[i]);
    printf("%d\n", path[i]);
}