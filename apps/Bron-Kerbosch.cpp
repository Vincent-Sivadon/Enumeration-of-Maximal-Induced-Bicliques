/*
    - Contient la première implémentation de Bron-Kerbosch
*/

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"
#include <assert.h>


int main() {
  // TEST 1
  std::unique_ptr<GraphMat> hex = makeHexagone<GraphMat>();
  
   std::set<u64> R;
   std::set<u64> X;
   std::set<u64> P;
   for (int i=0 ; i<hex->getSize() ; i++)
      P.insert(i);

   hex->changeToComplementary();
   hex->bronKerbosch(R, P, X);
   printSets(hex->cliques);

  return 0;
}