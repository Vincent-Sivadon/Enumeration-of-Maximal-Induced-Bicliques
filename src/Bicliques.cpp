#include "Graph.hpp"

#include <omp.h>
#include <mpi.h>

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
#pragma omp parallel for schedule(static)
    for (u64 i = 0; i < N; i++)
    {
        // S'il n'existe pas dans le graph, on passe au suivant
        if (!NodeExists(i)) continue;

        // Subgraph generation
        Graph subgraph = GenSubgraph(i);

        // Get max ind sets
        // Tree tree; std::set<u64> set;
        // subgraph.GetMaxIndSets(tree, set, i);
        // std::set<std::set<u64>> max_ind_sets = tree.getMaxBranches();
        subgraph.GetMaxIndSetsBK();

        // Pour chaque maximal set indépendant
        for (auto set : subgraph.cliques)
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


void Graph::GetBicliquesParallel()
{
    // Pour stocker les bicliques
    Tree suffixTree;

    // MPI Initialization
    int nproc, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Iteration repartition
    u64 Q = N / nproc;
    u64 R = N % nproc;
    u64 nb_iter = (rank < R ? Q + 1 : Q);
    u64 i_first = (rank < R ? rank * (Q + 1) : (rank - R) * Q + R * (Q + 1));

    // Pour chaque noeud du sommet
#pragma omp parallel for schedule(dynamic)
    for (u64 i = i_first; i < i_first+nb_iter; i++)
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
                #pragma omp critical
                suffixTree.insert(set);
        }
    }

    // Get only maximal branches of the subtree
    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

    std::string filename("bicliques" + std::to_string(rank));
    FILE *fp = fopen(filename.c_str(), "w");
    for (const auto &biclique : bicliques) {
    for (const auto &node : biclique) fprintf(fp, "%llu ", node);
    fprintf(fp, "\n");
    }
    fclose(fp);

    MPI_Finalize();
}

std::set<std::set<u64>> Graph::GetBicliques2()
{
    // Pour stocker les bicliques
    Tree suffixTree;

    // Re-order the graph according to the degeneracy order
    double start = omp_get_wtime();
    ChangeToDegeneracyOrder();
    double end = omp_get_wtime();
    std::cout << "Ordering : " << end-start << std::endl;

    start = omp_get_wtime();

    // Pour chaque noeud du sommet
#pragma omp parallel for schedule(guided)
    for (u64 i = 0; i < N; i++)
    {
        // Subgraph generation
        std::vector<Graph> subgraphs = GenSubgraphGik(i);

        for (auto& subgraph : subgraphs)
        {
            // Maximal independant sets
            subgraph.GetMaxIndSetsBK();

            // Pour chaque maximal set indépendant
            for (auto set : subgraph.cliques)
            {
                // Renommer les noeuds pour correspondance avec le graphe père
                set = renameSet(set, subgraph.parentIdx);

                #pragma omp critical
                suffixTree.insert(set);
            }
        }
    }

    end = omp_get_wtime();
    std::cout << "Treatment : " << end-start << std::endl;

    // Get only maximal branches of the subtree
    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

    return bicliques;
}