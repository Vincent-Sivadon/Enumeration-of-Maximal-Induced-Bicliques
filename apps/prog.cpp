#include "Graph.hpp"

#include <iostream>
#include <vector>

int main(int argc, char **argv) {

  Graph g = make_hexagone();
  std::set<std::set<u64>> bicliques = g.GetBicliques();
  printSets(bicliques);

  return 0;
}