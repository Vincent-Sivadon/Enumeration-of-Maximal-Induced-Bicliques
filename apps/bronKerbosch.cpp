/*
    - Contient la première implémentation de Bron-Kerbosch
*/

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"
#include "ReadFile.hpp"
#include <assert.h>

int main(int argc, char **argv) {
  u64 N;
  //argc>1 ? N = atoll(argv[1]) : printf("Usage : %s [N]\n", argv[0]);

  // TEST 1
  //std::unique_ptr<Graph> g = std::make_unique<GraphMat>(N);
  //g->randomize();
  //std::unique_ptr<Graph> g = initFromFile<GraphMat>("../data/edges.csv");
  
  //auto sub = g->genSubgraph(0);
  auto hex =  makeHexagone<GraphList>();
  auto h2o = makeH2O<GraphList>();
  hex->GraphList::getMaxIndSetsBK2();
  printSets(hex->cliques2);
  //h2o->getMaxIndSetsBK2();
  //printSets(h2o->cliques);

  //for (int i=0 ; i<N ; i++)
  //{
  //  auto sub = g->genSubgraph(i);
  //  sub->getMaxIndSetsBK();
  //}

  return 0;
}