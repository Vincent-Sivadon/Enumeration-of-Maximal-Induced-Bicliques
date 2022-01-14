#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <set>
#include <omp.h>

#include "graphes.hpp"

int main() {
    // SET SIZES
    // ------------------------------------
    int N = 10; // number of mesures
    u64 minSize = 10, maxSize = 500;
    u64 sizes[N];
    for(int i=0 ; i<N ; i++)
        sizes[i] = minSize + i*(maxSize-minSize)/N;
    

    for(const auto& n : sizes)
    {
        double tmp = 0;
        for(int i=0 ; i<10 ; i++)
        {
            GL::Graph g = GL::genRandGraph(n);

            double before = omp_get_wtime();
            std::set<std::set<u64>> bicliques = g.getBicliques();
            double after  = omp_get_wtime();
            tmp += (after-before);
        }
        std::cout << n << " " << tmp/10.0 << std::endl;

    }

    return 0;
}