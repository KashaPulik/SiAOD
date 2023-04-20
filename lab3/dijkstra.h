#include "./graph.h"

void shortest_path_dijkstra(struct graph* g, int src, int** D, int** prev);
int search_shortest_path(struct graph* g, int src, int dst, int** path);