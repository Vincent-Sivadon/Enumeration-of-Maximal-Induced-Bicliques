#include <iostream>
#include <set>
#include <stdlib.h>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"
#include <assert.h>
#include <omp.h>

// Dessine un hexagone
int main() {
  // std::unique_ptr<GraphMat> g = makeHexagone<GraphMat>();
  auto hex = makeHexagone<GraphList>();
  auto h2o = makeH2O<GraphList>();


  hex->connect(0, 3);
  hex->connect(4, 2);

  auto Gik = hex->genSubgraphGik(0);
  std::cout << " size: " << Gik.size() << '\n';

  Gik[2]->print();

  // std::set<std::set<u64>> bicliques = g->getBicliques();
  // g->drawBiclique(*bicliques.begin());
  // g->changeToComplementary();
  // g->draw();

  return 0;
}