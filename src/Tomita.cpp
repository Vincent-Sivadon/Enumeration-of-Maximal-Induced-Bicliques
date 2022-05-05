#include "Graph.hpp"

#include <algorithm>

// Calcul de l'intersection de deux ensembles
std::set<u64> Graph::IntersectionOfSets(std::set<u64> &A, std::set<u64> &B) {
    std::set<u64> output;
    for (const auto& i : B) 
        if (A.find(i) != A.end())
            output.insert(i);
    
    return output;
}

// Check if clique viable
bool Graph::IsClique(std::set<u64> &edgeSets) {
    int n = edgeSets.size();
    bool status = true;
    if (n < 3) return false;
    for (auto i : edgeSets) {
        for (auto j : edgeSets) {
            if ((i != j) && !AreConnected(i,j))
            {
                status = false;
                break;
            }
        }
  }

  return status;
}

// calcul la différence ensembliste A\B
std::set<u64> Graph::DiffOfSets(std::set<u64> &A, std::set<u64> &B)
{
    std::set<u64>::iterator it;
    std::set<u64> output;
    for (auto i : A) 
        if (B.find(i) == B.end())
            output.insert(i);
    
    return output;
}

u64 Graph::ChooseMyPivot(std::set<u64> &CAND, std::set<u64> &SUB)
{
    u64 pivot;
    u64 maxSize = 0;

    for (const auto &u : SUB) {
        std::set<u64> gammaU = GetAllNeighboors(u);

        std::set<u64> inter = IntersectionOfSets(gammaU, CAND);

        if (inter.size() >= maxSize) {
            pivot = u;
            maxSize = inter.size();
        }
    }

    return pivot;
}

// Tomita algorithm to get maximal independant sets (stored in cliques)
void Graph::ExpandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q)
{
    if (SUBG.empty())
    {
        if (IsClique(Q))
            cliques.insert(Q);
    }
    else
    {
        u64 currentPivot = ChooseMyPivot(SUBG, CAND);

        std::set<u64> gammaPivot = GetAllNeighboors(currentPivot);
        
        std::set<u64> EXTu = DiffOfSets(CAND, gammaPivot);

        while (not EXTu.empty()) {
            u64 q = *(EXTu.begin());
            Q.insert(q);

            std::set<u64> gammaQ = GetAllNeighboors(q);
            std::set<u64> SUBGq = IntersectionOfSets(SUBG, gammaQ);
            std::set<u64> CANDq = IntersectionOfSets(CAND, gammaQ);
            ExpandTomita(SUBGq, CANDq, Q);

            std::set<u64> singleq = {q};

            CAND = DiffOfSets(CAND, singleq);
            Q = DiffOfSets(Q, singleq);
            EXTu = DiffOfSets(CAND, gammaPivot);
        }
    }
}

// Get max ind set Tomita wrapper
void Graph::GetMaxIndSetsTTT() {
    std::set<u64> vertices;
    for (int i=0 ; i<N ; i++)
        vertices.insert(i);
    std::set<u64> Q;
    
    ChangeToComplementary();
    ExpandTomita(vertices, vertices, Q);
}