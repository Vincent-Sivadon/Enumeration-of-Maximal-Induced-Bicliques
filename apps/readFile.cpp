#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"

#include "ReadFile.hpp"

// Dessine un hexagone
int main() {
  std::unique_ptr<Graph> g = initFromFile<GraphList>("../data/edges.csv");

  return 0;
}