#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>

#include <SDL2/SDL.h>

#include "graphes.hpp"

// Dessine un hexagone
int main() {
    Graph<Lst> g = Hexagone<Lst>();
    g.draw();


    return 0;
}