#pragma once

#include <vector>
#include <iostream>

typedef unsigned long long u64;

struct Graph {
    u64 N = 0;  // size
    std::vector<std::vector<u64>> adj;
    Graph() {};
    Graph(u64 n) {adj.resize(n) ; N=n;}

    // Print the graph in terminal
    void print();
    // connect two vertices i and j
    void connect(u64 i, u64 j);
    // return true if i and j are neighboors
    bool areConnected(u64 i, u64 j);
};

Graph H2O();

// Generate a graph that represent a methane molecule (for testing purposes)
Graph Methane();

// Generate a graph that represent an hexagone
Graph Hexagone();