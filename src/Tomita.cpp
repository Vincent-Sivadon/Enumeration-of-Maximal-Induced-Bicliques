#include "Graph.hpp"

void Graph::ExpandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q)
{
    /*
    if (SUBG.empty())
    {
        if (isClique(Q))
            cliques.insert(Q);
    }
    else
    {
        u64 currentPivot = ChooseMyPivot(SUBG, CAND);

        std::set<u64> gammaPivot;

        for (u64 i = 0; i < N; i++) 
            if (adj[currentPivot * N + i] == 1)
                gammaPivot.insert(i);
        
        std::set<u64> EXTu = diffOfSets(CAND, gammaPivot);

        while (not EXTu.empty()) {
            u64 q = *(EXTu.begin());
            // int q = randchoice(EXTu);
            Q.insert(q);
            // std::cout << q << ", ";
            std::set<u64> gammaQ;
            for (u64 i = 0; i < N; i++) {
            if (adj[currentPivot * N + i] == 1) gammaQ.insert(i);
            }
            std::set<u64> SUBGq = intersectionOfSets(SUBG, gammaQ);
            std::set<u64> CANDq = intersectionOfSets(CAND, gammaQ);
            ExpandTomita(SUBGq, CANDq, Q);
            std::set<u64> singleq = {q};
            // CAND.pop_back(q);
            // Q.pop_back(q);
            // Q = diffOfSets(Q,singleq);
            CAND = diffOfSets(CAND, singleq);
            // std::cout << "back, ";
            Q = diffOfSets(Q, singleq);
            EXTu = diffOfSets(CAND, gammaPivot);
            // std::cout << "back, ";
        }
    }
    */
}