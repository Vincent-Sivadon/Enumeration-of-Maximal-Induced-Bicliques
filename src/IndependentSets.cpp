#include "Graph.hpp"

bool Graph::IsConnectedToSet(u64 i, const std::set<u64>& set)
{
    for (const auto& node : set)
        if (AreConnected(i, node)) return true;
    return false;
}

void Graph::GetMaxIndSets(Tree& tree, std::set<u64>& tmp_set, u64 i)
{
  for (u64 j = i; j < N; j++) {
    // Check if node exists
    if (!NodeExists(j)) continue;

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