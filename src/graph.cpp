#include "visualisation.hpp"
#include "graph.hpp"

// connect 2 vertices i and j
void Graph::connect(u64 i, u64 j) {
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
bool Graph::areConnected(u64 i, u64 j) {
    for (auto& vertex : adj[i])
        if (vertex == j) return true;
    return false;
}


void Graph::draw() {
    drawGraph(*this);
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