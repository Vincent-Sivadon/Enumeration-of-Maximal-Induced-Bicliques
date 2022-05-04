#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <omp.h>

int main(int argc, char **argv) {
    Graph g = make_hexagone();
    g.Connect(2, 4);
    g.Connect(0, 3);

    std::set<std::set<u64>> bicliques = g.GetBicliques();
    printSets(bicliques);
  return 0;
}