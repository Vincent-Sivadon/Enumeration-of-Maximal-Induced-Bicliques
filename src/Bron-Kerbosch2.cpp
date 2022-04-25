/*
    - Contient la seconde implémentation de Bron-Kerbosch
*/

#include "Graph.hpp"

/* ========================== BRON-KERBOSCH ========================== */


void Graph::bronKerbosch2(std::set<u64> R, std::set<u64> P, std::set<u64> X)
{

    std::set<u64> r,p1,p2,x,u1;

    if(P.empty() && X.empty())
        cliques1.insert(R);

    for(auto k : P)
    {
        u1 = u(X, k);
    }

    for(auto i : u1)
    {
        p1 = inter(P, i);
    }

    for(auto v : p1)
        {
            r = u(R,v);
            p2 = inter(P, v);
            x = inter(X, v);
            bronKerbosch2(r,p2,x);
            P.erase(v);
            X.insert(v);
        }
}

void Graph::prepareBron2()
{
  std::set<u64> R, P, X;

  for(auto i = 0; i < N; i++)
    P.insert(i);

  bronKerbosch2(R, P, X);
}
/*
// Enumère tout les sets indépendants maximaux du graphe
std::set<std::set<u64>> Graph::getMaxIndSets3() {
  //
  std::map<u64, std::set<u64>> IndSets;
    std::set<std::set<u64>> maxIndSets;

    // Maximal set size
    u64 maxSize = 0;

    for(auto i : cliques)
        if(i.size() > maxSize)
            maxSize = i.size();

    for(auto i : cliques)
        if(i.size() == maxSize)
            maxIndSets.insert(i);

  return maxIndSets;
}
*/