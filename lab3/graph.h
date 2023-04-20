#pragma once

#include <stdio.h>
#include <stdlib.h>

#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

struct graph {
    int nvertices;
    int* m;
    int* visited;
};

void graph_clear(struct graph* g);
struct graph* graph_create(int nvertices);
void graph_free(struct graph* g);
void graph_set_edge(struct graph* g, int i, int j, int w);
int graph_get_edge(struct graph* g, int i, int j);
void print_graph(struct graph* g);
struct graph* make_connected_graph(int nvertices, int weight);
struct graph* make_lattice_graph(int side_length, int weight);
void print_pathlens(struct graph* g, int src);
void print_path(int pathlen, int* path);