#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>
#include <omp.h>

#include "graphes.hpp"

template <typename T>
double perf(int N)
{
    double time = 0;

    // On moyenne sur 10 samples
    for (int i = 0; i < 10; i++)
    {
        Graph<T> g = genRandGraph<T>(N);

        double before = omp_get_wtime();
        std::set<std::set<u64>> bicliques = g.getBicliques();
        double after = omp_get_wtime();

        time += (after - before);
    }

    return time / 10;
}

template <typename T>
double perfParallel(int N)
{
    double time = 0;

    // On moyenne sur 10 samples
    for (int i = 0; i < 10; i++)
    {
        Graph<T> g = genRandGraph<T>(N);

        double before = omp_get_wtime();
        std::set<std::set<u64>> bicliques = g.getBicliquesParallel();
        double after = omp_get_wtime();

        time += (after - before);
    }

    return time / 10;
}

int main(int argc, char **argv)
{
    // Tailles des graphes utilisés pour les mesures de performances :
    int N = 10;       // nombre de mesure
    u64 minSize = 10; // plus petite taille
    u64 maxSize;

    // Si pas d'argument donnée à l'exécution, on prend une taille max par défaut
    if (argc <= 1)
        maxSize = 50;
    else
        maxSize = atoll(argv[1]);

    // Liste des tailles
    u64 sizes[N];
    for (int i = 0; i < N; i++)
        sizes[i] = minSize + i * (maxSize - minSize) / N;

    // Pour chaque taille n
    for (const auto &n : sizes)
    {
        double matTime = perf<Mat>(n);
        double matParallelTime = perfParallel<Mat>(n);

        double lstTime = perf<Lst>(n);
        double lstParallelTime = perfParallel<Lst>(n);

        std::cout << n << " " << lstTime << " " << matTime << " " << lstParallelTime << " " << matParallelTime << std::endl;
    }

    return 0;
}