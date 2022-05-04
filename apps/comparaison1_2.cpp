#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <omp.h>

int main(int argc, char **argv) {
  if (argc<2)
  {
    printf("Usage : %s [N]", argv[0]);
    return 1;
  } u64 N = atoll(argv[1]);

  Graph g(N);
  g.Randomize();

  double start = omp_get_wtime();
  std::set<std::set<u64>> bicliques = g.GetBicliques();
  double end = omp_get_wtime();

  std::cout << end - start << std::endl;

  double start2 = omp_get_wtime();
  std::set<std::set<u64>> bicliques2 = g.GetBicliques2();
  double end2 = omp_get_wtime();
  
  std::cout << end2-start2 << std::endl;

  return 0;
}