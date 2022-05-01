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
  
   std::set<u64> R = {};
   std::set<u64> X = {};

   std::set<u64> P = hex->prepareBron();

   for(auto v : P)
    std::cout<<v<<std::endl;
   
   std::set<std::set<u64>> cliques1 = hex->Graph::bronKerbosch(R, P, X);
   printSets(cliques1);
   /*std::set<std::set<u64>> maxIndSets = hex->Graph::getMaxIndSets2(cliques1);

  std::set<std::set<u64>> expected = {{0, 2, 4}, {1, 3, 5}};
  for (auto &set : maxIndSets) assert(expected.find(set) == expected.end());
  

  // TEST 2
  auto meth = Graph::makeMethane<GraphList>();

  //P = meth -> Graph::prepareBron(R,P,X);

   std::set<std::set<u64>> cliques1bis = meth->Graph::bronKerbosch(R, P, X);

   std::set<std::set<u64>> maxIndSets2 = meth->getMaxIndSets2(cliques1bis);
   //meth->changeToComplementary();

  std::set<u64> expected2 = {1, 2, 3, 4};
  for (auto &set : maxIndSets2) assert(set != expected2);
printSets(cliques1bis);
  /*

  // TEST 1
  auto hex2 = Graph::makeHexagone<GraphList>();
  // TEST 1

   std::set<std::set<u64>> cliques2 = hex2->Graph::bronKerbosch2(R, P, X);

  std::set<std::set<u64>> maxIndSets3 = hex2->Graph::getMaxIndSets2(cliques2);
  hex2->changeToComplementary();

  for (auto &set : maxIndSets3) assert(expected.find(set) == expected.end());

  hex2->draw();

  // TEST 2
  auto meth2 = Graph::makeMethane<GraphList>();

   std::set<std::set<u64>> cliques2bis = meth2->Graph::bronKerbosch2(R, P, X);

   std::set<std::set<u64>> maxIndSets4 = meth2->getMaxIndSets2(cliques2bis);
   meth2->changeToComplementary();

  for (auto &set : maxIndSets4) assert(set != expected2);

  meth2->draw();*/

  return 0;
}