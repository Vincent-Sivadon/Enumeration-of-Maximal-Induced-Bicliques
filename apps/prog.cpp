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
    std::set<std::set<u64>> bicliques = g.GetBicliques2();
    double end = omp_get_wtime();
    // printSets(bicliques);
    std::cout << "Total " << end - start << std::endl;
  return 0;
}