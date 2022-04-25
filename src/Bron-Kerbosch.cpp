/*
    - Contient la première implémentation de Bron-Kerbosch
*/

#include "Graph.hpp"

/* ========================== BRON-KERBOSCH ========================== */

// L'algorithme de Bron Kerbosch utilise l'union et l'intersection
//d'ensembles, on commence donc par implémenter une fonction union et inter. 

std::set<u64> u(std::set<u64> uni, u64 v)
{
    uni.insert(v);
    return uni;
}

/*Pour la fonction intersection, 
il faut obtenir le set et les voisions du second élément*/

std::set<u64> inter(std::set<u64> set, u64 v)
{
    std::set<u64> intersection;

    for(auto k=set.begin(); k != set.end(); k++)
        if (Graph::areConnected(v, *k)) 
            intersection.insert(v);        
    return intersection;
}

std::set<std::set<u64>> cliques1;

std::set<std::set<u64>> bronKerbosch(std::set<u64> R, std::set<u64> P, std::set<u64> X)
{

    std::set<u64> r,p,x;

    if(P.empty() && X.empty())
        cliques1.insert(R);
    else 
    {
        for(auto v : P)
        {
            r = u(R,v);
            p = inter(P, v);
            x = Graph::inter(X, v);
            bronKerbosch(r,p,x);
            P.erase(v);
            X.insert(v);
        }
    }

  return cliques1;
}

void Graph::prepareBron()
{
  std::set<u64> R, P, X;

  for(auto i = 0; i < N; i++)
    P.insert(i);

  bronKerbosch(R, P, X);
}

// Enumère tout les sets indépendants maximaux du graphe
std::set<std::set<u64>> Graph::getMaxIndSets2() {
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

