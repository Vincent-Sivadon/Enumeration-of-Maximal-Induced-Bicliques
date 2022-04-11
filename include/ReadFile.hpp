/* Contient les utilitaires pour transformer les données d'un fichier .csv en Graph */

#pragma once

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"

#include <string>

// Run through file to get number of nodes
u64 getNumberOfNodes(std::string filename);

// Create graph from .csv file
template<typename T>
std::unique_ptr<Graph> initFromFile(std::string filename) {
  u64 N = getNumberOfNodes(filename);
  std::unique_ptr<Graph> g = std::make_unique<T>(N);
  std::cout << N << std::endl;

  return g;
}