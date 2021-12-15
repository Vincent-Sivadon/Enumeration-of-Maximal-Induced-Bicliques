#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>

#include "SDL2/SDL.h"

#include "graph.hpp"

void insertProperSuffixes(std::set<int> maxIndSet, std::set<std::set<int>> bicliques) {
    std::set<int> properSuffixes;
    for(auto& el : maxIndSet) {
        properSuffixes.insert(el);
        bicliques.insert(properSuffixes);
    }
}

int main() {
    // Size
    int N = 10;

    // Store sets
    std::set<std::set<int>> bicliques;

    // Define some graph
    Graph g = genRandGraph(10);
    
    //
    int id_acc = 0;
    for(int i=0 ; i<N ; i++) {
        // Construct the subgraph G_i
        Graph subgraph_i = g.genSubgraph(i);

        // Get all maximal independent sets of G_i
        std::set<std::set<int>> maxIndSets = subgraph_i.getMaxIndSets();

        for(auto& maxIndSet : maxIndSets) {
            if (subgraph_i.isProper(maxIndSet)) {
                // Search if maxIndSet is already in bicliques
                if (bicliques.find(maxIndSet) == bicliques.end())
                    insertProperSuffixes(maxIndSet, bicliques);
            }
        }

    }

    return 0;
}