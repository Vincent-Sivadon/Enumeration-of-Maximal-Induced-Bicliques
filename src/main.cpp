#include <iostream>
#include <unordered_map>
#include <stdlib.h>

#include "SDL2/SDL.h"

#include "graph.hpp"

// Insert graph in the graphTable unordered_map
void insertGraph(std::unordered_map<int, Graph>& graphTable, Graph& graph) {
    if (graphTable.find(graph.id) != graphTable.end()) {
        graph.id = rand();
        insertGraph(graphTable, graph);
    }
    graphTable.insert({graph.id, graph});
}

int main() {
    // Store graphs
    std::unordered_map<int, Graph> graphTable;

    // Define some graph
    Graph rgraph = genRandGraph(10);
    Graph h2o = H2O();
    Graph hex = Hexagone();

    insertGraph(graphTable, rgraph);
    insertGraph(graphTable, h2o);
    insertGraph(graphTable, hex);
    
    std::cout << "--------BEFORE--------" << std::endl;
    std::cout << rgraph.id << std::endl;
    std::cout << h2o.id << std::endl;
    std::cout << hex.id << std::endl;
    
    std::cout << "--------AFTER--------" << std::endl;
    for( auto& pair : graphTable) {
        Graph graph = pair.second;
        std::cout << graph.id << std::endl;
    }

    hex.draw();
    

    return 0;
}