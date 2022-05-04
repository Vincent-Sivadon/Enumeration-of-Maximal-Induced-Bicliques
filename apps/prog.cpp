#include "Graph.hpp"

#include <iostream>
#include <vector>

int main(int argc, char **argv) {

  Graph g(5);
  g.Connect(0, 1);
  g.Connect(0, 4);
  g.Connect(1, 4);
  g.Connect(1, 3);
  g.Connect(1, 2);
  g.Connect(2, 3);
  g.Connect(3, 4);

  g.ChangeToDegeneracyOrder();
  printVec(g.sigma);


  return 0;
}