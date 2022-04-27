/*
    - Contient la première implémentation de Bron-Kerbosch
*/

#include "Graph.hpp"
#include "GraphList.hpp"

#include <gtest/gtest.h>
#include <assert.h>


int main(){
  // TEST 1
  auto hex = Graph::makeHexagone<GraphList>();
  // TEST 1

   std::set<u64> R = {};
   std::set<u64> X = {};
   std::set<u64> P = {};

   //std::set<u64> 
   //P = hex->Graph::prepareBron(R, P, X); 
   std::set<std::set<u64>> cliques1 = hex->Graph::bronKerbosch(R, P, X);

  std::set<std::set<u64>> maxIndSets = hex->Graph::getMaxIndSets2(cliques1);
  hex->changeToComplementary();
  std::set<std::set<u64>> expected = {{0, 2, 4}, {1, 3, 5}};
  for (auto &set : maxIndSets) assert(expected.find(set) == expected.end());

  hex->draw();

  // TEST 2
  auto meth = Graph::makeMethane<GraphList>();

   std::set<std::set<u64>> cliques1bis = meth->Graph::bronKerbosch(R, P, X);

   std::set<std::set<u64>> maxIndSets2 = meth->getMaxIndSets2(cliques1bis);
   meth->changeToComplementary();

  std::set<u64> expected2 = {1, 2, 3, 4};
  for (auto &set : maxIndSets2) assert(set != expected2);

  meth->draw();

  printf("Hello World\n");
  return 0;
}