#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>

#include <SDL2/SDL.h>

#include "graphes.hpp"

// Dessine un hexagone
int main()
{
    Graph<Lst> g = Hexagone<Lst>();
    g.connect(0, 3);
    g.connect(4, 2);
    g.connect(0, 2);
    std::set<std::set<u64>> bicliques = g.getBicliquesParallel();
    auto it = bicliques.begin();
    g.drawBiclique(*it);

    return 0;
}