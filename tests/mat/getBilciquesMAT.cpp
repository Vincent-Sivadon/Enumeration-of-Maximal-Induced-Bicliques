#include <assert.h>

#include "graphesMat.hpp"

int main() {
    GM::Graph hex = GM::Hexagone();
    hex.connect(0, 3);
    hex.connect(4, 2);
    hex.connect(0, 2);
    std::set<std::set<u64>> hex_bicliques = hex.getBicliques();


    std::set<std::set<u64>> expected = 
        {
            {0, 1, 3, 5}, {0, 2, 4, 5}, {0, 3, 4, 5}
        };

    for (auto& set : hex_bicliques)
        assert(expected.find(set) != expected.end());


   return 0;
}