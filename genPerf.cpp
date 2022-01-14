#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>
#include <omp.h>

#include "graphes.hpp"

int main(int argc, char** argv) {
    // Tailles des graphes utilisés pour les mesures de performances :
    int N = 10;             // nombre de mesure
    u64 minSize = 10;       // plus petite taille
    u64 maxSize;
    if (argc<=1) {
        std::cout << "Par défaut la taille du graphe maximale est prise à 100, mais elle est spécifiable par : " << argv[0] << " [Taille Maximale]" << std::endl;
        maxSize = 100;
    } else { maxSize = atoll(argv[1]) ;}

    // Liste des tailles
    u64 sizes[N];
    for(int i=0 ; i<N ; i++)
        sizes[i] = minSize + i*(maxSize-minSize)/N;
    
    // Pour chaque taille n
    for(const auto& n : sizes)
    {
        // Va stocker la moyenne du temps d'execution pour les 10 samples
        double tmp = 0;

        // On moyenne sur 10 samples
        for(int i=0 ; i<10 ; i++)
        {
            // Initialization d'un nouveau graphe aléatoire
            GL::Graph g = GL::genRandGraph(n);

            double before = omp_get_wtime();
            std::set<std::set<u64>> bicliques = g.getBicliques();
            double after  = omp_get_wtime();

            //
            tmp += (after-before);
        }

        // Temps moyen d'execution pour une taille n  :  tmp/10
        std::cout << n << " " << tmp/10.0 << std::endl;
    }

    return 0;
}