#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>
#include <omp.h>

#include "graphes.hpp"
#include "graphesMat.hpp"

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
        double tmpLst = 0;
        double tmpMat = 0;

        // On moyenne sur 10 samples
        for(int i=0 ; i<10 ; i++)
        {
            // Initialization d'un nouveau graphe aléatoire
            GL::Graph gLst = GL::genRandGraph(n);  // version liste d'adjacence
            GM::Graph gMat = GM::genRandGraph(n);  // version matrice d'adjacence

            double beforeLst = omp_get_wtime();
            std::set<std::set<u64>> bicliquesLst = gLst.getBicliques();
            double afterLst  = omp_get_wtime();

            double beforeMat = omp_get_wtime();
            std::set<std::set<u64>> bicliquesMat = gMat.getBicliques();
            double afterMat  = omp_get_wtime();

            //
            tmpLst += (afterLst - beforeLst);
            tmpMat += (afterMat - beforeMat);            
        }

        // Temps moyen d'execution pour une taille n  :  tmp/10
        std::cout << n << " " << tmpLst/10.0 << " " << tmpMat/10.0 << std::endl;
    }

    return 0;
}