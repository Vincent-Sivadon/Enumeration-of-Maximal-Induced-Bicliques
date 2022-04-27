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
  std::unique_ptr<GraphList> g = makeHexagone<GraphList>();
  g->connect(0, 3);
  g->connect(4, 2);
  g->connect(0, 2);
  std::set<std::set<u64>> bicliques = g->getBicliques();
  g->drawBiclique(*bicliques.begin());

  return 0;
}