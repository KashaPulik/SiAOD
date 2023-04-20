#include "./dijkstra.h"
#include "./graph.h"

int main()
{
    struct graph* g = make_connected_graph(10, 9);
    print_graph(g);
    graph_set_edge(g, 1, 2, 9);
    print_graph(g);
    print_pathlens(g, 1);
    print_shortest_path(g, 1, 2);
    free(g);
    g = make_lattice_graph(3, 9);
    print_graph(g);
    print_pathlens(g, 1);
    print_shortest_path(g, 1, 9);
}