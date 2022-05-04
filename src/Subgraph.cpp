#include "Graph.hpp"

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

Graph Graph::GenSubgraph(u64 i)
{
    // Ensemble des sommets à distance 1 et 2
    std::set<u64> nodes_at_1 = GetNeighboorsVi(i);
    std::set<u64> nodes_at_2;
    for(const auto& node : nodes_at_1)
        for (const auto& node2 : GetNeighboorsVi(node))
            nodes_at_2.insert(node2);

    for (const auto& node : nodes_at_1)
        std::cout << node << " ";
    std::cout << std::endl;

    u64 subgraphSize = nodes_at_1.size() + nodes_at_2.size() + 1;
    Graph subgraph(subgraphSize);

    subgraph.SetParentIndices(*this, nodes_at_1, nodes_at_2, i);
    
    for (const auto& x : nodes_at_1)
    {
        for (const auto& y : nodes_at_1)
            if (x != y && AreConnected(x, y))
                subgraph.Connect(x,y);
        for (const auto& y : nodes_at_2)
            if (!AreConnected(x,y))
                subgraph.Connect(x,y);
    }
    for (const auto& x : nodes_at_2)
        for (const auto& y : nodes_at_2)
            if (x != y && AreConnected(x,y))
                subgraph.Connect(x,y);            

    return subgraph;
}
