#include <assert.h>

#include "graphesMat.hpp"

int main() {
    GM::Graph hex = GM::Hexagone();
    hex.connect(0, 3);
    hex.connect(4, 2);
    hex.connect(0, 2);
    std::set<std::set<u64>> hex_bicliques = hex.getBicliques();
    /* Should have the max induced bicliques
        0 ----- 2
          -   - 
            -
          -   -
        4 ----- 3
    */

   return 0;
}