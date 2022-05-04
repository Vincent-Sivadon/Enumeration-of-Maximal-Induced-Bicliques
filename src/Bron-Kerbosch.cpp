#include "Graph.hpp"

void Graph::ChangeToComplementary()
{
  for (int i=0 ; i<N ; i++)
    for (int j=0 ; j<N ; j++)
        if (NodeExists(i) && NodeExists(j))
            (adj[i*N + j] == 0 && i!=j) ? adj[i*N + j] = 1 : adj[i*N + j] = 0;

}	

std::set<u64> Graph::InterSetAndNeighboors(std::set<u64>& set, u64 v)
{
    std::set<u64> intersection = set;
    
    for(const auto& k : set)
        if (!AreConnected(v, k)) 
          intersection.erase(k);

    return intersection;
}

void Graph::BronKerbosch(std::set<u64>& R, std::set<u64>& P, std::set<u64>& X)
{
    if (P.empty() && X.empty())
        cliques.insert(R);

    while (!P.empty())
    {        
        const auto v = P.begin();

        std::set<u64> r = R; r.insert(*v);
        std::set<u64> p = InterSetAndNeighboors(P,*v);
        std::set<u64> x = InterSetAndNeighboors(X,*v);

        BronKerbosch(r, p, x);
        
        P.erase(*v);
        X.insert(*v);
    }
}

void Graph::GetMaxIndSetsBK()
{
   std::set<u64> R;
   std::set<u64> X;
   std::set<u64> P;
   for (int i=0 ; i<N ; i++)
      if(NodeExists(i)) P.insert(i);

   ChangeToComplementary();
   BronKerbosch(R, P, X);
}