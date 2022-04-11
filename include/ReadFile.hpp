/* Contient les utilitaires pour transformer les données d'un fichier .csv en Graph */

#pragma once

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Run through file to get number of nodes
u64 getNumberOfNodes(std::string filename);

// Connect 2 nodes from a string line of type : node_i,node_j
void connectFromLine(std::string line, std::unique_ptr<Graph> &g);

// Create graph from .csv file
template<typename T>
std::unique_ptr<Graph> initFromFile(std::string filename) {
  u64 N = getNumberOfNodes(filename);
  std::unique_ptr<Graph> g = std::make_unique<T>(N);

  std::string line;

  std::fstream file(filename);
  if (file.is_open()) {
    while (getline(file, line)) connectFromLine(line, g);
  }

  return g;
}