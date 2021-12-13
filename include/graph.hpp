#pragma once

#include <vector>
#include <stdlib.h>

typedef unsigned long long u64;

struct Graph {
    u64 N = 0;  // size
    int id = rand();
    std::vector<std::vector<u64>> adj;
    Graph() {};
    Graph(u64 n) {adj.resize(n) ; N=n;}

    // Print the graph in terminal
    void print();
    // connect two vertices i and j
    void connect(u64 i, u64 j);
    // return true if i and j are neighboors
    bool areConnected(u64 i, u64 j);
    // draw the graph
    void draw();
};

//
Graph genRandGraph(u64 N);

Graph H2O();

// Generate a graph that represent a methane molecule (for testing purposes)
Graph Methane();

// Generate a graph that represent an hexagone
Graph Hexagone();