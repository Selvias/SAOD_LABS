#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct graph {
    int vertexes;
    int **m;             //matrix n x n
    int *visited;
};

graph *graph_create(int vertexes);
void graph_init(graph *g);
void graph_free (graph *g);
void graph_set_edge_weight(graph *g, int i, int j, int w);
int graph_get_edge_weight(graph *g, int i, int j);
void graph_DFS(graph *g, int v);
void graph_print(graph *g);