/* */

#include "ReadFile.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Run through file to get number of nodes
u64 getNumberOfNodes(std::string filename) {
  u64 max = 0;
  std::string line, word;

  std::fstream file(filename);
  if (file.is_open()) {
    while (getline(file, line)) {
      std::stringstream str(line);
      getline(str, word, ',');

      u64 N = std::stoull(word, nullptr, 0);
      if (N > max) max = N;
    }
  }

  return max;
}