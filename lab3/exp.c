#include "./dijkstra.h"
#include "./graph.h"
#include <sys/time.h>
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    struct graph* g = make_connected_graph(10000, 100);
    int *D, *prev;
    double time = wtime();
    shortest_path_dijkstra(g, 1, &D, &prev);
    time = wtime() - time;
    printf("Average time: %.3f sec\n", time);
    free(D);
    free(prev);
    graph_free(g);
    g = make_lattice_graph(100, 100);
    time = wtime();
    shortest_path_dijkstra(g, 1, &D, &prev);
    time = wtime() - time;
    printf("Average time: %.3f sec\n", time);
    free(D);
    free(prev);
    graph_free(g);
}