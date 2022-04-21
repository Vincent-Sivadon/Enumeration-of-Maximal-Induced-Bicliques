#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"

#include "ReadFile.hpp"

#include <iostream>
#include <omp.h>

// Dessine un hexagone à partir d'un fichier .csv
int main() {
  std::unique_ptr<Graph> g = initFromFile<GraphMat>("../data/edges.csv");

  return 0;
}