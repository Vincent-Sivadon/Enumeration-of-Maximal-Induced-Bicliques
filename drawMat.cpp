#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>

#include <SDL2/SDL.h>

#include "graphesMat.hpp"

// Dessine un hexagone
int main() {
    GM::Graph g = GM::Hexagone();
    g.draw();

    std::set<std::set<u64>> bicliques = g.getBicliques();

    return 0;
}