/* */

#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <omp.h>
#include <math.h>

int main(int argc, char **argv)
{
    // Get size
    if (argc<2)
    {
		printf("Usage : %s [N]", argv[0]);
		return 1;
    } u64 N = atoll(argv[1]);

    // Declare graphs
    Graph g(N);
    Graph gBK(N);
    Graph gTTT(N);

    // Init graph
    g.Randomize();
    gBK.Randomize();
    gTTT.Randomize();

    // Mesure the time for enumeration of bicliques
    double start = omp_get_wtime();
    Tree tree; std::set<u64> set;
    g.GetMaxIndSets(tree, set, 0);
    std::set<std::set<u64>> max_ind_sets = tree.getMaxBranches();
    double end = omp_get_wtime();

    double startBK = omp_get_wtime();
    gBK.GetMaxIndSetsBK();
    double endBK = omp_get_wtime();

    double startTTT = omp_get_wtime();
    gTTT.GetMaxIndSetsTTT();
    double endTTT = omp_get_wtime();

    std::cout << N << " "
              << end-start << " "
              << endBK-startBK << " "
              << endTTT-startTTT << " "
              << std::endl;



  return 0;
}