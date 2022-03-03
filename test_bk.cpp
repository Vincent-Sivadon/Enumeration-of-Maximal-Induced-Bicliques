#include <assert.h>
#include <set>
#include <iostream>

#include "bron-kerbosch.hpp"


template <typename T>
void test()
{
    // TEST 1
    Graph<T> hex = Hexagone<T>();
    std::set<std::set<u64>> maxIndSets = hex.getMaxIndSets();
    std::set<std::set<u64>> expected = 
        {
            {0, 2, 4}, {1, 3, 5}
        };
    for (auto& set : maxIndSets)
        assert(expected.find(set) != expected.end());

    // TEST 2
    Graph<T> meth = Methane<T>();
    std::set<std::set<u64>> maxIndSets2 = meth.getMaxIndSets();
    std::set<u64> expected2 = {1, 2, 3, 4};
    for(auto& set : maxIndSets2)
        assert(set == expected2);
}

int main() {

    // Lance les tests version liste
    test<Lst>();


   return 0;
}