#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>

#include "SDL2/SDL.h"

#include "graph.hpp"


int main() {
    Graph g = Hexagone();
    g.draw();

    std::set<std::set<u64>> bicliques = g.getBicliques();

    return 0;
}