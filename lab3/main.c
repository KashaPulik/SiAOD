#include "./dijkstra.h"
#include "./graph.h"

// int main()
// {
//     struct graph* g = make_connected_graph(10, 1);
//     int* D = malloc(g->nvertices * sizeof(int));
//     int* prev = malloc(g->nvertices * sizeof(int));
//     shortest_path_dijkstra(g, 1, D, prev);
//     print_pathlens(g, D);
//     int pathlen;
//     int* path = NULL;
//     pathlen = search_shortest_path(g, 1, 5, &path);
//     print_path(pathlen, path);
//     graph_clear(g);
//     free(D);
//     free(prev);
//     free(path);
//     g = make_lattice_graph(3, 1);
//     D = malloc(g->nvertices * sizeof(int));
//     prev = malloc(g->nvertices * sizeof(int));
//     shortest_path_dijkstra(g, 1, D, prev);
//     print_pathlens(g, D);
//     print_graph(g);
//     pathlen = search_shortest_path(g, 1, 15, &path);
//     print_path(pathlen, path);
// }

int main()
{
    struct graph* g = make_lattice_graph(3, 1);
    // print_graph(g);
    int* D = malloc(g->nvertices * sizeof(int));
    int* prev = malloc(g->nvertices * sizeof(int));
    shortest_path_dijkstra(g, 1, D, prev);
    print_pathlens(g, D);
    int pathlen;
    int* path = NULL;
    pathlen = search_shortest_path(g, 1, 7, &path);
    print_path(pathlen, path);
}