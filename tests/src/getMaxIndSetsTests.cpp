#include <assert.h>
#include <set>
#include <iostream>

#include "graphes.hpp"
#include "../graph_tests.hpp"

void printSets(std::set<std::set<u64>> sets)
{
    for(auto& set : sets) {
        for(auto& i : set) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

void getMaxIndSetsTests()
{
    // TEST 1
    Graph hex = Hexagone();
    std::set<std::set<u64>> maxIndSets = hex.getMaxIndSets();
    std::set<std::set<u64>> expected = 
        {
            {0, 2, 4}, {1, 3, 5}
        };
    for (auto& set : maxIndSets)
        assert(expected.find(set) != expected.end());

    // TEST 2
    Graph meth = Methane();
    std::set<std::set<u64>> maxIndSets2 = meth.getMaxIndSets();
    std::set<u64> expected2 = {1, 2, 3, 4};
    for(auto& set : maxIndSets2)
        assert(set == expected2);
}