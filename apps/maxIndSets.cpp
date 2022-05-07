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
    Graph gBKpiv(N);
    Graph gTTT(N);
    
    // Stat variables
    int nb_samples = 4;    // Number of samples
    double meanBKpiv = 0;        // Average times
    double meanTTT = 0;        // Average times
    double stdBKpiv;             // Standard deviation
    double stdTTT;             // Standard deviation
    std::vector<double> timesBKpiv(nb_samples);  // Each iteration time
    std::vector<double> timesTTT(nb_samples);  // Each iteration time

    // Make nb_samples mesures
    for (int i = 0; i < nb_samples; i++)
    {
        // Init graph
        gBKpiv.Randomize();
        gTTT.Randomize();

        double startBKpiv = omp_get_wtime();
        Tree tree; std::set<u64> tmp;
        gBK.GetMaxIndSets(tree, tmp, 0);
        double endBKpiv = omp_get_wtime();

        double startTTT = omp_get_wtime();
        gTTT.GetMaxIndSetsBK();
        double endTTT = omp_get_wtime();

        // Store times
        timesBKpiv[i]  = endBKpiv  - startBKpiv;
        timesTTT[i]    = endTTT    - startTTT;
        meanBKpiv      += endBKpiv - startBKpiv;
        meanTTT        += endTTT   - startTTT;
    }

    // Standard deviation computation
    // ------------------------------
    meanBKpiv  /= nb_samples;
    meanTTT    /= nb_samples;
    for (int i = 0; i < nb_samples; i++)
    {
        stdBKpiv   += fabs(meanBKpiv  - timesBKpiv[i] )  * fabs(meanBKpiv   - timesBKpiv[i] );
        stdTTT     += fabs(meanTTT    - timesTTT[i]   )  * fabs(meanTTT     - timesTTT[i]   );
    }
    stdBKpiv /= nb_samples;    
    stdTTT   /= nb_samples;    

    std::cout << N << "   "
              << meanBKpiv  << " " << stdBKpiv  << "   "
              << meanTTT    << " " << stdTTT    << "   "
              << std::endl;

  return 0;
}