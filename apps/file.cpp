#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <omp.h>

int main(int argc, char **argv) {
    Graph g;
    g.InitFromFile("../data/facebook.csv");

    double start = omp_get_wtime();
    std::set<std::set<u64>> bicliques = g.GetBicliques2();
    double end = omp_get_wtime();
    std::cout << end - start << std::endl;

  return 0;
}