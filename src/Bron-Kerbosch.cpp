#include "Graph.hpp"

// Modify the graph to be it's complementary
void Graph::ChangeToComplementary()
{
  for (int i=0 ; i<N ; i++)
    for (int j=0 ; j<N ; j++)
        (adj[i*N + j] == 0 && i!=j) ? adj[i*N + j] = 1 : adj[i*N + j] = 0;

}	

// Get the intersection of set and neighbors of v
std::set<u64> Graph::InterSetAndNeighboors(std::set<u64>& set, u64 v)
{
    std::set<u64> intersection = set;
    
    for(const auto& k : set)
        if (!AreConnected(v, k)) 
          intersection.erase(k);

    return intersection;
}

// Insert graph maximal independant sets in cliques
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

// BronKerbosch function call wrapper
void Graph::GetMaxIndSetsBK()
{
   std::set<u64> R;
   std::set<u64> X;
   std::set<u64> P;
   for (int i=0 ; i<N ; i++)
      P.insert(i);

   ChangeToComplementary();
   BronKerbosch(R, P, X);
}


// Insert graph maximal independant sets in cliques
void Graph::BronKerboschPivot(std::set<u64>& R, std::set<u64>& P, std::set<u64>& X)
{
    if (P.empty() && X.empty())
        cliques.insert(R);

    // Choose pivot
    std::set<u64> P_inter_X = IntersectionOfSets(P,X);

    // Find max degree in P_inter_X
    u64 max_degree = 0;
    u64 pivot;
    for (const auto& node : P_inter_X)
    {
        u64 degree = GetDegree(node);
        if (degree >= max_degree)
        {
            max_degree = degree;
            pivot = node;
        }
    }

    // Create set p1
    std::set<u64> p1;
    for (const auto& node : P)
        if (!AreConnected(node, pivot))
            p1.insert(node);

    for (const auto& v : p1)
    {
        std::set<u64> r  = R; r.insert(v);
        std::set<u64> p2 = InterSetAndNeighboors(P, v);
        std::set<u64> x  = InterSetAndNeighboors(X, v);

        BronKerboschPivot(r, p2, x);

        P.erase(v);
        X.insert(v);
    }
    
}

// BronKerbosch function call wrapper
void Graph::GetMaxIndSetsBKpivot()
{
   std::set<u64> R;
   std::set<u64> X;
   std::set<u64> P;
   for (int i=0 ; i<N ; i++)
      P.insert(i);

   ChangeToComplementary();
   BronKerbosch(R, P, X);
}