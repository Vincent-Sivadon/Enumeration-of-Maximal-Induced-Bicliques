#include <iostream>
#include <omp.h>
#include <set>
#include <stdlib.h>
#include <unordered_map>

#include "Graph.hpp"
#include "GraphList.hpp"
#include "GraphMat.hpp"

template<typename T>
double perfParallel(int N) {
  double time = 0;

  // On moyenne sur 10 samples
  for (int i = 0; i < 10; i++) {
    std::unique_ptr<Graph> g = std::make_unique<T>(N);
    g->randomize();

    double before = omp_get_wtime();
    std::set<std::set<u64>> bicliques = g->getBicliquesParallel();
    double after = omp_get_wtime();

    time += (after - before);
  }

  return time / 10;
}

template<typename T>
double perfParallelBK(int N) {
  double time = 0;

  // On moyenne sur 10 samples
  for (int i = 0; i < 10; i++) {
    std::unique_ptr<Graph> g = std::make_unique<T>(N);
    g->randomize();

    double before = omp_get_wtime();
    std::set<std::set<u64>> bicliques = g->getBicliquesParallelBK();
    double after = omp_get_wtime();

    time += (after - before);
  }

  return time / 10;
}


int main(int argc, char **argv) {
  // Tailles des graphes utilisés pour les mesures de performances :
  int N = 10;         // nombre de mesure
  u64 minSize = 10;   // plus petite taille
  u64 maxSize;

  // Si pas d'argument donnée à l'exécution, on prend une taille max par défaut
  if (argc <= 1) maxSize = 50;
  else
    maxSize = atoll(argv[1]);

  // Liste des tailles
  u64 sizes[N];
  for (int i = 0; i < N; i++) sizes[i] = minSize + i * (maxSize - minSize) / N;

  // Pour chaque taille n
  for (const auto &n : sizes) {
    double mat_parallel = perfParallel<GraphMat>(n);
    double mat_parallel_BK = perfParallelBK<GraphMat>(n);
    double list_parallel = perfParallel<GraphList>(n);
    double list_parallel_BK = perfParallelBK<GraphList>(n);

    std::cout << n << " "
              << list_parallel << " "
              << list_parallel_BK << " "
              << mat_parallel
              << mat_parallel_BK
              << std::endl;
  }

  return 0;
}