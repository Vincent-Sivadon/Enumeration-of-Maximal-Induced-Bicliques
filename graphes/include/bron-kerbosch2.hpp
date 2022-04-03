/*
    - Contient l'implémentation de l'algo 2 de Bron-Kerbosch. 
*/

#pragma once
#include <set>
#include <vector>
#include <iostream>
#include <map>


typedef unsigned long long u64;

/* ========================== BRON-KERBOSCH ========================== */

template <typename T>
void Graph<T>::bronKerbosch2(std::set<u64> R, std::set<u64> P, std::set<u64> X)
{

    std::set<u64> r,p1,p2,x;

    if(P.empty() && X.empty())
        cliques.insert(R);

    auto u1 = u(P, X)[1];
    p1 = inter(P, u1);
    
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

template <typename T>
void Graph<T>::prepareBron2()
{
  std::set<u64> R, P, X;

  for(auto i = 0; i < N; i++)
    P.insert(i);

  bronKerbosch2(R, P, X);
}


template <typename T>
std::set<std::set<u64>> Graph<T>::getMaxIndSets3() {
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