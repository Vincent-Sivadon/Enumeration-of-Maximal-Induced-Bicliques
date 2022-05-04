#include "Graph.hpp"

#include <map>

void Graph::SetParentIndices(const Graph& parentGraph, std::set<u64>& nodes_at_1, std::set<u64>& nodes_at_2, u64 pivot)
{
    parentIdx.resize(N);
    std::vector<bool> visited(N, false);

    parentIdx[0] = pivot;
    visited[0] = true;

    // Define parent indices
    for (u64 idx = 1; idx < N; idx++)
    {
        // Search for the node in those lists that has the min sigma
        u64 min_sigma = INF;
        u64 node_of_min_sigma;
        for (const auto& node : nodes_at_1)
            if (parentGraph.sigma[node] < min_sigma && !visited[node])
            {
                min_sigma = parentGraph.sigma[node];
                node_of_min_sigma = node;
            }
        for (const auto& node : nodes_at_2)
            if (parentGraph.sigma[node] < min_sigma && !visited[node])
            {
                min_sigma = parentGraph.sigma[node];
                node_of_min_sigma = node;
            }

        // The node of index idx in subgraph corresponds to node_of_min_sigma
        parentIdx[idx] = node_of_min_sigma;
        visited[node_of_min_sigma] = true;
    }
}

// Rename nodes we've extracted from the parent graph
std::map<u64,u64> renameNodes(std::vector<u64>& indices)
{
    std::map<u64,u64> childIndices;

    for (u64 i = 0; i < indices.size(); i++)
        childIndices.insert(std::make_pair(indices[i], i));

    return childIndices;    
}

Graph Graph::GenSubgraph(u64 i)
{
    // Ensemble des voisins à distance 1
    std::set<u64> neighboors = GetAllNeighboors(i);

    // On ne garde que ceux qui sont supérieur dans sigma
    std::set<u64> nodes_at_1;
    for (const u64& node : neighboors)
        if (sigma[node]>=sigma[i] && node!=i)
            nodes_at_1.insert(node);

    // Ensemble des voisins à distance 2
    std::set<u64> nodes_at_2;
    for(const auto& node : neighboors)
        for (const auto& node2 : GetNeighboorsVi(node, i))
            nodes_at_2.insert(node2);

    // Création du sous-graphe
    u64 subgraphSize = nodes_at_1.size() + nodes_at_2.size() + 1;
    Graph subgraph(subgraphSize);

    // Nommage des sites pour correspondance avec le graphe original
    subgraph.SetParentIndices(*this, nodes_at_1, nodes_at_2, i);
    std::map<u64,u64> child_idx = renameNodes(subgraph.parentIdx);
    
    // Détermination des liens entre les sites du sous-graphe
    for (const auto& x : nodes_at_1)
    {
        for (const auto& y : nodes_at_1)
            if (AreConnected(x, y))
                subgraph.Connect(child_idx[x],child_idx[y]);
        for (const auto& y : nodes_at_2)
            if (!AreConnected(x,y))
                subgraph.Connect(child_idx[x],child_idx[y]);
    }
    for (const auto& x : nodes_at_2)
        for (const auto& y : nodes_at_2)
            if (AreConnected(x,y))
                subgraph.Connect(child_idx[x],child_idx[y]);

    return subgraph;
}
