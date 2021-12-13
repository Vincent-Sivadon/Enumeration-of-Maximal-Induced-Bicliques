#pragma once

#include <vector>
#include <stdlib.h>
#include <set>


struct Graph {
    int N = 0;  // size
    int id = rand();
    std::vector<std::vector<int>> adj;
    Graph() {};
    Graph(int n) {adj.resize(n) ; N=n;}

    // Print the graph in terminal
    void print();
    // connect two vertices i and j
    void connect(int i, int j);
    // return true if i and j are neighboors
    bool areConnected(int i, int j);
    // draw the graph
    void draw();
    // is the set proper to Graph ?
    bool isProper(std::set<int> set);
};

// Generates a graph in wich two vertices has a 50% chance of beeing connected
Graph genRandGraph(int N);

// Generate a graph that represent a water molecule (for testing purposes)

Graph H2O();

// Generate a graph that represent a methane molecule (for testing purposes)
Graph Methane();

// Generate a graph that represent an hexagone (for testing purposes)
Graph Hexagone();