#include <assert.h>
#include <set>
#include <iostream>

#include "graphesMat.hpp"


int main()
{
    // TEST 1
    GM::Graph hex = GM::Hexagone();
    std::set<std::set<u64>> maxIndSets = hex.getMaxIndSets();
    std::set<std::set<u64>> expected = 
        {
            {0, 2, 4}, {1, 3, 5}
        };
    for (auto& set : maxIndSets)
        assert(expected.find(set) != expected.end());

    // TEST 2
    GM::Graph meth = GM::Methane();
    std::set<std::set<u64>> maxIndSets2 = meth.getMaxIndSets();
    std::set<u64> expected2 = {1, 2, 3, 4};
    for(auto& set : maxIndSets2)
        assert(set == expected2);

    return 0;
}