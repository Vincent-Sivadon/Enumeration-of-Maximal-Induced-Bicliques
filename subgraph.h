#pragma once

#include <limits.h>
#include <stdbool.h>

#include "adjlst.h"

int minDist(int* dist, bool* visited, int N);

void printPath(int* dist, int N);

int* dijkstra(Graph* graph, int src, int limit);