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
    Tree suffixTree;

    for (u64 i = 0; i < N; i++)
    {
        if (!NodeExists(i)) continue;

        // Subgraph generation
        Graph subgraph = GenSubgraph(i);

        // Get max ind sets
        Tree tree;
        std::set<u64> set;
        subgraph.GetMaxIndSets(tree, set, 0);
        std::set<std::set<u64>> max_ind_sets = tree.getMaxBranches();

        printSets(max_ind_sets);
        std::cout << "-----" << std::endl;

        for (auto set : max_ind_sets)
        {
            set = renameSet(set, subgraph.parentIdx);

            if (IsProper(set))
                suffixTree.insert(set);
        }
    }

    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

    return bicliques;
}
