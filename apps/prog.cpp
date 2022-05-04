#include "Graph.hpp"

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  Graph g(6);
  g.sigma[0] = 2;
  g.sigma[1] = 5;
  g.sigma[2] = 4;
  g.sigma[3] = 1;
  g.sigma[4] = 0;
  g.sigma[5] = 3;
  g.Connect(0,1);
  g.Connect(0,5);
  g.Connect(1,2);
  g.Connect(2,3);
  g.Connect(3,4);
  g.Connect(4,5);
  g.Connect(0,3);
  g.Connect(4,2);

  Graph subgraph = g.GenSubgraph(0);
  subgraph.Print();
  std::cout << "-------------\n";
  for (const auto& el : subgraph.parentIdx)
    std::cout << el << " ";
  std::cout << std::endl;

  return 0;
}