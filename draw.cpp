#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>

#include <SDL2/SDL.h>

#include "graphes.hpp"

// Dessine un hexagone
int main() {
    GL::Graph g = GL::Hexagone();
    g.draw();

    std::set<std::set<u64>> bicliques = g.getBicliques();

    return 0;
}