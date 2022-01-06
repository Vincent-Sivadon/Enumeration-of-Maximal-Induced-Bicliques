#pragma once

#include <vector>
#include <stdlib.h>
#include <set>
#include <map>

typedef unsigned long long u64;

struct Graph {
    std::map<u64, std::set<u64>> adj;

    // Print the graph in terminal
    void print();
    // draw the graph
    void draw();

    // EDGES
    // connect two vertices i and j
    void connect(u64 i, u64 j);
    // return true if i and j are neighboors
    bool areConnected(u64 i, u64 j);

    // is the set proper to Graph ?
    bool isProper(std::set<u64> set);

    // Subgrpah generation
    // Get the shortest path from src to any vertex
    std::vector<u64> shortestPaths(u64 src);
    Graph genSubgraph(u64 i);

    bool isNotConnectedToSet(u64 vertex, std::set<u64> set);
    std::set<std::set<u64>> getMaxIndSets();

    // Generate all the maximal induced bicliques of Graph according to the paper
    std::set<std::set<u64>> getBicliques();

};

// Generates a graph in wich two vertices has a 50% chance of beeing connected
Graph genRandGraph(u64 N);

// Generate a graph that represent a water molecule (for testing purposes)

Graph H2O();

// Generate a graph that represent a methane molecule (for testing purposes)
Graph Methane();

// Generate a graph that represent an hexagone (for testing purposes)
Graph Hexagone();

// Get the vertex for wich the dist to src is minimal (used)
u64 minDist(std::vector<u64>& dist, std::vector<bool>& visited);
