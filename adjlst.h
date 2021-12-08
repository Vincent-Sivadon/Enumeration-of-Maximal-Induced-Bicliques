#pragma once

#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Vertex struct
typedef struct Vertex {
    int index;
    struct Vertex* next;
} Vertex;


// Graph struct
typedef struct {
    int size;
    Vertex** adjlst;
} Graph;


// Create a Vertex
Vertex* createVertex(int i);

// Add edge between two vertices s and d
void addEdge(Graph* graph, int s, int d);

// Print the graph in terminal
void printGraph(Graph* graph);

// Check if an edge can be placed between 2 vertices s and d
int checkEdge(Graph* graph, int s, int d);

// Declare a graph
Graph* createGraph(int N);

// Generate random graph
Graph* genRandGraph(int N);


// SIMPLE GENERIC GRAPHS --------------------------------------------------

// Generate a graph that represent a H2O molecule (to test checkEdge)
Graph* H2O();
// Generate a graph that represent a methane molecule (to test checkEdge)
Graph* Methane();
// Generate a graph that represent an hexagone
Graph* Hexagone();
