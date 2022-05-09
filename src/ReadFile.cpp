/* */

#include "ReadFile.hpp"

#include <vector>

// Run through file to get number of nodes
u64 getNumberOfNodes(std::string filename) {
  u64 max = 0;
  std::string line, i_str, j_str;

  std::fstream file(filename);
  if (file.is_open()) {
    while (getline(file, line)) {
      std::stringstream str(line);
      getline(str, i_str, ',');
      getline(str, j_str, ',');

      u64 N_i = std::stoull(i_str, nullptr, 0);
      u64 N_j = std::stoull(j_str, nullptr, 0);

      if (N_i > max) max = N_i;
      if (N_j > max) max = N_j;
    }
  }

  return max + 1;
}

// Connect 2 nodes from a string line of type : node_i,node_j
void connectFromLine(std::string line, std::unique_ptr<Graph> &g) {
  std::string i_str, j_str;

  std::stringstream str(line);
  getline(str, i_str, ',');
  getline(str, j_str, ',');

  u64 i = stoull(i_str, nullptr, 0);
  u64 j = stoull(j_str, nullptr, 0);

  g->connect(i, j);
}