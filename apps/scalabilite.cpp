/* Fait tourner nb_samples fois l'énumération de bicliques pour un graphe de N=5000 noeuds
 * A la fin affiche la moyenne et l'écart-type */

#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <omp.h>
#include <math.h>

int main(int argc, char **argv)
{
    // Graph size
    u64 N = 5000;
    Graph g(N);
    
    // Stat variables
    int nb_samples = 10;    // Number of samples
    double mean = 0;        // Average times
    double std;             // Standard deviation
    std::vector<double> times(nb_samples);  // Each iteration time

    // Make nb_samples mesures
    for (int i = 0; i < nb_samples; i++)
    {
        // Init graph
        g.Randomize();

        // Mesure the time for enumeration of bicliques
        double start = omp_get_wtime();
        std::set<std::set<u64>> bicliques = g.GetBicliques2();
        double end = omp_get_wtime();
        
        // Store times
        times[i] = end-start;
        mean += end-start;
    }

    // Standard deviation computation
    // ------------------------------
    mean /= nb_samples;
    for (int i = 0; i < nb_samples; i++)
        std += fabs(mean - times[i]) * fabs(mean - times[i]);
    std /= nb_samples;    

    std::cout << mean << " " << std << std::endl;

  return 0;
}