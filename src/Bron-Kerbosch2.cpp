/*
    - Contient la seconde implémentation de Bron-Kerbosch
*/

#include "Graph.hpp"

/* ========================== BRON-KERBOSCH ========================== */

std::set<std::set<u64>> cliques2;

std::set<std::set<u64>> Graph::bronKerbosch2(std::set<u64> R, std::set<u64> P, std::set<u64> X)
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

    return cliques2;
}


