#include <iostream>
#include <set>
#include <stdlib.h>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <omp.h>

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"

// Dessine un hexagone
int main() {
  std::unique_ptr<Graph> g = std::make_unique<GraphMat>(100);
  g->randomize();
  //std::set<std::set<u64>> bicliques = g->getBicliques_ALGO_2();

    // For every nodes
  #pragma omp parallel for schedule(dynamic)
    for (u64 i = 0; i < 100; i++) {
      // Construct the subgraph G_i
      auto subgraph_i = g->genSubgraph(i);
    }

  return 0;
}