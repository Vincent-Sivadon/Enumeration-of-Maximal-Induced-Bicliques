/* Lance l'algo 2 sur un graphe initialisé à partir d'un .csv */

#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <omp.h>
#include <mpi.h>

int main(int argc, char **argv) {
    Graph g;
    g.InitFromFile("../networks/facebook.csv");

    MPI_Init(NULL,NULL);

    double start = omp_get_wtime();
    g.GetBicliques2();
    double end = omp_get_wtime();

    std::cout << end-start << std::endl;
  return 0;
}
