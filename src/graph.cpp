#include <vector>
#include <iostream>
#include <fstream>

#include "visualisation.hpp"
#include "graph.hpp"

// connect 2 vertices i and j
void Graph::connect(int i, int j) {
    adj[i].push_back(j);
    adj[j].push_back(i);
}

void Graph::print() {
    for (int v = 0; v < N; ++v)
    {
        std::cout << "\n Neighboors of vertex "
             << v << "\n ";
        for (auto x : adj[v])
           std::cout << "-> " << x;
        printf("\n");
    }
}

// Check if an edge can be placed between 2 vertices s and d
bool Graph::areConnected(int i, int j) {
    for (auto& vertex : adj[i])
        if (vertex == j) return true;
    return false;
}


void Graph::draw() {
    drawGraph(*this);
}

Graph genRandGraph(int N) {
    Graph graph(N);

    for(int i=0 ; i<N ; i++)
        for(int j=0 ; j<N ; j++) {
            double r = (double) rand() / (double) RAND_MAX;
            if (r < 0.5) graph.connect(i, j);
        }
    
    return graph;
}

bool Graph::isProper(std::set<int> set) {
    for (int i=0 ; i<N ; i++) 
        if(set.find(i) == set.end()) return true;
    return false;
}


// Generate a graph that represent a H2O molecule (for testing purposes)
Graph H2O() {
    Graph graph(3);
    graph.connect(0, 1);
    graph.connect(0, 2);

    return graph;
}

// Generate a graph that represent a methane molecule (for testing purposes)
Graph Methane() {
    Graph graph(5);
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(0, 4);

    return graph;
}

// Generate a graph that represent an hexagone
Graph Hexagone() {
    Graph graph(6);

    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 4);
    graph.connect(4, 5);
    graph.connect(5, 0);
    
    return graph;
}