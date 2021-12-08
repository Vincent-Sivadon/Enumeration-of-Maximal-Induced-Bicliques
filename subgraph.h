#pragma once

#include <limits.h>
#include <stdbool.h>

#include "adjlst.h"

// A utility function to find the vertex with minimum distance value
int minDist(int* dist, bool* visited, int N);

// Print Dijkstra results
void printPath(int* dist, int N);

// Dijkstra path finding algorithm
int* dijkstra(Graph* graph, int src, int limit);

// Create a subgraph G_i
Graph* genSubgraph(Graph* graph, int i);