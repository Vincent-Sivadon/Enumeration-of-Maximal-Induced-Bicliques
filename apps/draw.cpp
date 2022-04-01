#include <iostream>
#include <set>
#include <stdlib.h>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"

// Dessine un hexagone
int main() {
  std::unique_ptr<GraphList> g = Graph::makeHexagone<GraphList>();
  g->connect(0, 3);
  g->connect(4, 2);
  g->connect(0, 2);
  g->drawBiclique({0, 2, 4, 5});

  return 0;
}