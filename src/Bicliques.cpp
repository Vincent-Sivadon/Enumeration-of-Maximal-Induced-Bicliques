#include "Graph.hpp"

/* Rename set from parent indices */
std::set<u64> renameSet(std::set<u64>& set, std::vector<u64>& indices)
{
    std::set<u64> renamedSet;
    for (const auto& node : set)
        renamedSet.insert(indices[node]);

    return renamedSet;        
}

bool Graph::IsProper(std::set<u64>& set)
{
    for (const auto& i : set)
        for (const auto& j : set)
            if (i!=j)
                if (AreConnected(i, j))
                    return true;

  return false;
}

std::set<std::set<u64>> Graph::GetBicliques()
{
    // Pour stocker les bicliques
    Tree suffixTree;

    // Pour chaque noeud du sommet
    for (u64 i = 0; i < N; i++)
    {
        // S'il n'existe pas dans le graph, on passe au suivant
        if (!NodeExists(i)) continue;

        // Subgraph generation
        Graph subgraph = GenSubgraph(i);

        // Get max ind sets
        Tree tree; std::set<u64> set;
        subgraph.GetMaxIndSets(tree, set, i);
        std::set<std::set<u64>> max_ind_sets = tree.getMaxBranches();

        // Pour chaque maximal set indépendant
        for (auto set : max_ind_sets)
        {
            // Renommer les noeuds pour correspondance avec le graphe père
            set = renameSet(set, subgraph.parentIdx);

            // Check if is proper, insert bicliques if it's the case
            if (IsProper(set))
                suffixTree.insert(set);
        }
    }

    // Get only maximal branches of the subtree
    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

    return bicliques;
}
