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

// Algorithm 1
std::set<std::set<u64>> Graph::GetBicliques()
{
    /************************** MPI Initialization **************************/
    
    int nproc;                              // Number of MPI process
    int rank;                               // ID of the current running process
    MPI_Init(NULL, NULL);                   // Allows us to make MPI calls
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);  // Get nproc
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get rank
    // Iteration repartition
    u64 Q = N / nproc;
    u64 R = N % nproc;
    // R rank will have Q+1 iterations, and the other (nproc-R) will have Q
    // So R*(Q+1) + (nproc-R)*Q = R*Q + R + nproc*Q - R*Q = Q*nproc + R
    u64 nb_iter = (rank < R ? Q + 1 : Q);
    u64 i_first = (rank < R ? rank * (Q + 1) : (rank - R) * Q + R * (Q + 1));
    
    
    /******************************* Algorithm *******************************/

    // Pour stocker les bicliques
    Tree suffixTree;

    // Pour chaque noeud du sommet
#pragma omp parallel for schedule(static)
    for (u64 i = i_first; i < i_first+nb_iter; i++)
    {
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
                #pragma omp critical
                suffixTree.insert(set);
        }
    }

    // Get only maximal branches of the subtree
    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();



    /******************************* Output *******************************/

    // Every MPI process will create a file an write the bicliques he found
    std::string filename("bicliques" + std::to_string(rank));
    FILE *fp = fopen(filename.c_str(), "w");
    for (const auto &biclique : bicliques) {
        for (const auto &node : biclique)
            fprintf(fp, "%llu ", node);
        fprintf(fp, "\n");
    }
    fclose(fp);

    MPI_Finalize();

    return bicliques;
}


// Algorithm 2
std::set<std::set<u64>> Graph::GetBicliques2()
{
    /************************** MPI Initialization **************************/

    int nproc;                              // Number of MPI process
    int rank;                               // ID of the current running process
    MPI_Init(NULL, NULL);                   // Allows us to make MPI calls
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);  // Get nproc
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get rank
    // Iteration repartition
    u64 Q = N / nproc;
    u64 R = N % nproc;
    // R rank will have Q+1 iterations, and the other (nproc-R) will have Q
    // So R*(Q+1) + (nproc-R)*Q = R*Q + R + nproc*Q - R*Q = Q*nproc + R
    u64 nb_iter = (rank < R ? Q + 1 : Q);
    u64 i_first = (rank < R ? rank * (Q + 1) : (rank - R) * Q + R * (Q + 1));



    /******************************* Algorithm *******************************/

    // Pour stocker les bicliques
    Tree suffixTree;

    // Re-order the graph according to the degeneracy order
    ChangeToDegeneracyOrder();

    // Pour chaque noeud du sommet
#pragma omp parallel for schedule(static)
    for (u64 i = i_first; i < i_first+nb_iter; i++)
    {
        // Iteration performance mesuring
        double start = omp_get_wtime();

        // Subgraph generation
        std::vector<Graph> subgraphs = GenSubgraphGik(i);

        for (auto& subgraph : subgraphs)
        {
            // Maximal independant sets
            subgraph.GetMaxIndSetsBKpivot();

            // Pour chaque maximal set indépendant
            for (auto set : subgraph.cliques)
            {
                // Renommer les noeuds pour correspondance avec le graphe père
                set = renameSet(set, subgraph.parentIdx);

                #pragma omp critical
                suffixTree.insert(set);
            }
        }

        // Iteration performance mesuring
        double end = omp_get_wtime();
        // std::cout << end-start << "\n";
    }

    // Get only maximal branches of the subtree
    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();



    /******************************* Output *******************************/

    // Every MPI process will create a file an write the bicliques he found
    std::string filename("bicliques" + std::to_string(rank));
    FILE *fp = fopen(filename.c_str(), "w");
    for (const auto &biclique : bicliques) {
        for (const auto &node : biclique)
            fprintf(fp, "%llu ", node);
        fprintf(fp, "\n");
    }
    fclose(fp);

    MPI_Finalize();


    return bicliques;
}