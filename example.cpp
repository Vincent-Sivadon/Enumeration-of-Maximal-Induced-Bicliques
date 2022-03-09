#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>
#include <omp.h>

#include <SDL2/SDL.h>

#include "graphes.hpp"

// Dessine un hexagone
int main(int argc, char **argv)
{
    // Check number of arguments
    if (argc < 2)
    {
        printf("Usage : %s [Size]\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    Graph<Mat> g = genRandGraph<Mat>(N);

    double before = omp_get_wtime();
    std::set<std::set<u64>> bicliques = g.getBicliques();
    double after = omp_get_wtime();

    printf("Performance : %lf\n", after - before);

    // g.drawBiclique(*bicliques.begin());

    return 0;
}