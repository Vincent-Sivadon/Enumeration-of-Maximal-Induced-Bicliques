#include "Graph.hpp"


// Check if i is connected to a node of set in graph
bool Graph::IsConnectedToSet(u64 i, const std::set<u64>& set)
{
    for (const auto& node : set)
        if (AreConnected(i, node)) return true;
    return false;
}


// Check if a set is proper
bool Graph::IsProper(std::set<u64>& set)
{
    for (const auto& i : set)
        for (const auto& j : set)
            if (i!=j)
                if (AreConnected(i, j))
                    return true;

  return false;
}


// Get a list of maximal independant sets of graph
void Graph::GetMaxIndSets(Tree& tree, std::set<u64>& tmp_set, u64 i)
{
  for (u64 j = i; j < N; j++) {

    // On ajoute j au tmpSet si il n'est connecté à aucun k de tmpSet
    if (IsConnectedToSet(j, tmp_set)) continue;

    // Si on a passé le test, on insert j
    tmp_set.insert(j);

    // on refait la procédure à partir de j+1
    GetMaxIndSets(tree, tmp_set, j + 1);

    // Puisqu'on a construit le set indépendants qui partait de j, on le
    // supprime du tmpSet
    tmp_set.erase(j);
  }

  tree.insert(tmp_set);
}