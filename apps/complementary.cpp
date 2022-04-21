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
  std::unique_ptr<GraphMat> g = Graph::makeHexagone<GraphMat>();
  // std::set<std::set<u64>> bicliques = g->getBicliques();
  // g->drawBiclique(*bicliques.begin());
  g->changeToComplementary();
  g->draw();

  return 0;
}