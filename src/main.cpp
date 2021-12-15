#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>

#include "SDL2/SDL.h"

#include "graph.hpp"


int main() {
    Graph g = genRandGraph(10);

    std::set<std::set<int>> bicliques = g.getBicliques();

    return 0;
}