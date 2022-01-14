#include <assert.h>

#include "suffixTree.hpp"
#include "graphesMat.hpp"

int main()
{
    std::set<u64> set1 = {0,2,4};
    std::set<u64> set2 = {1,3,5};

    GM::Tree suffixTree;

    suffixTree.insert(set1);
    suffixTree.insert(set2);
    suffixTree.insert({0,2});

    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();
    std::set<std::set<u64>> expected = 
        {
            {0, 2, 4}, {1, 3, 5}
        };
    for (auto& set : bicliques)
        assert(expected.find(set) != expected.end());

    return 0;
}