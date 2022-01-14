#include <assert.h>
#include <set>
#include <iostream>

#include "graphes.hpp"

void printSets(std::set<std::set<u64>> sets)
{
    for(auto& set : sets) {
        for(auto& i : set) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    // TEST 1
    GL::Graph hex = GL::Hexagone();
    std::set<std::set<u64>> maxIndSets = hex.getMaxIndSets();
    std::set<std::set<u64>> expected = 
        {
            {0, 2, 4}, {1, 3, 5}
        };
    for (auto& set : maxIndSets)
        assert(expected.find(set) != expected.end());

    // TEST 2
    GL::Graph meth = GL::Methane();
    std::set<std::set<u64>> maxIndSets2 = meth.getMaxIndSets();
    std::set<u64> expected2 = {1, 2, 3, 4};
    for(auto& set : maxIndSets2)
        assert(set == expected2);

    return 0;
}