#include "Graph.hpp"

#include <iostream>
#include <vector>

int main(int argc, char **argv) {

  Graph g = make_hexagone();
  g.Connect(0, 3);
  g.Connect(4, 2);

  std::vector<Graph> subgraphs = g.GenSubgraphGik(1);
  subgraphs[0].Print();
  printVec(subgraphs[0].parentIdx);

  return 0;
}