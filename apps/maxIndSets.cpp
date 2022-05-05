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
    
    // Stat variables
    int nb_samples = 10;    // Number of samples
    double mean = 0;        // Average times
    double meanBK = 0;        // Average times
    double meanTTT = 0;        // Average times
    double std;             // Standard deviation
    double stdBK;             // Standard deviation
    double stdTTT;             // Standard deviation
    std::vector<double> times(nb_samples);  // Each iteration time
    std::vector<double> timesBK(nb_samples);  // Each iteration time
    std::vector<double> timesTTT(nb_samples);  // Each iteration time

    // Make nb_samples mesures
    for (int i = 0; i < nb_samples; i++)
    {
        // Init graph
        g.Randomize();
        gBK.Randomize();
        gTTT.Randomize();

        // Mesure the time for enumeration of bicliques
        double start = omp_get_wtime();
        Tree tree; std::set<u64> set;
        g.GetMaxIndSets(tree, set, i);
        std::set<std::set<u64>> max_ind_sets = tree.getMaxBranches();
        double end = omp_get_wtime();

        double startBK = omp_get_wtime();
        gBK.GetMaxIndSetsBK();
        double endBK = omp_get_wtime();

        double startTTT = omp_get_wtime();
        gTTT.GetMaxIndSetsTTT();
        double endTTT = omp_get_wtime();

        // Store times
        times[i]    = end-start;
        timesBK[i]  = endBK-startBK;
        timesTTT[i] = endTTT-startTTT;
        mean       += end-start;
        meanBK     += endBK-startBK;
        meanTTT    += endTTT-startTTT;
    }

    // Standard deviation computation
    // ------------------------------
    mean    /= nb_samples;
    meanBK  /= nb_samples;
    meanTTT /= nb_samples;
    for (int i = 0; i < nb_samples; i++)
    {
        std     += fabs(mean    - times[i])     * fabs(mean     - times[i]   );
        stdBK   += fabs(meanBK  - timesBK[i])   * fabs(meanBK   - timesBK[i] );
        stdTTT  += fabs(meanTTT - timesTTT[i])  * fabs(meanTTT  - timesTTT[i]);
    }
    std /= nb_samples;    
    stdBK /= nb_samples;    
    stdTTT /= nb_samples;    

    std::cout << mean    << " " << std    << "   "
              << meanBK  << " " << stdBK  << "   "
              << meanTTT << " " << stdTTT << "   "
              << std::endl;

  return 0;
}