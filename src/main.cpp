#include "SDL2/SDL.h"

#include "graph.hpp"

int main() {
    Graph graph = genRandGraph(10);
    graph.draw();

    return 0;
}