#include <iostream>
#include <omp.h>
#include <set>
#include <stdlib.h>
#include <unordered_map>

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"
#include "ReadFile.hpp"

// Dessine un hexagone
int main(int argc, char *argv[]) {
  // Get number of nodes
  if (argc < 2) {
    std::cout << "Usage : " << argv[0] << " [edges.csv]\n";
    return 1;
  }
  u64 N = atoll(argv[1]);

  std::unique_ptr<Graph> g = std::make_unique<GraphMat>(N);
  g->randomize();

  double start = omp_get_wtime();
  std::set<std::set<u64>> bicliques = g->getBicliquesParallelBK();
  double end = omp_get_wtime();

  std::cout << "Perf : " << end - start << std::endl;

  return 0;
}