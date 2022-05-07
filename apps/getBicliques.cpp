/* Display : average of GetBicliques and Standard Deviation for a graph of size given in argument */

#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <omp.h>
#include <mpi.h>
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
    
    MPI_Init(&argc, &argv);

    // Init graph
    g.Randomize();

    double start2 = omp_get_wtime();
    g.GetBicliques2();
    double end2 = omp_get_wtime();


    //std::cout << N << " "
    //          << end2-start2
    //          << std::endl;

  return 0;
}