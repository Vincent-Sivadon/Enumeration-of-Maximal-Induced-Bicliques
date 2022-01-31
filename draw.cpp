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
    g.drawBiclique({0, 2, 4, 5});

    return 0;
}