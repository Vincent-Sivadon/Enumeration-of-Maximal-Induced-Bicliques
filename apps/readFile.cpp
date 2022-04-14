#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"

#include "ReadFile.hpp"

#include <iostream>

// Dessine un hexagone à partir d'un fichier .csv
int main() {
  std::unique_ptr<Graph> g = initFromFile<GraphList>("../data/edges.csv");
  g->draw();

  return 0;
}