#include <assert.h>

#include "StructGraph.hpp"
#include "suffixTree.hpp"


int main()
{
     std::set<u64> set1 = {0, 2, 4};
    std::set<u64> set2 = {1, 3, 5};
    std::set<u64> set3 = {2, 3};

    Tree suffixTree;

    suffixTree.insert(set1);
    suffixTree.insert(set2);
    suffixTree.insert({0, 2});
    suffixTree.insert(set3);

    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();
    std::set<std::set<u64>> expected =
        {
            {0, 2, 4}, {1, 3, 5}};

    for (auto &set : bicliques)
        assert(expected.find(set) != expected.end()); 

    return 0;
}