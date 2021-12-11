#include "SDL2/SDL.h"

#include "graph.hpp"
#include "visualisation.hpp"

int main() {
    Graph hex = Hexagone();
    Graph methane = Methane();
    methane.draw();

    return 0;
}