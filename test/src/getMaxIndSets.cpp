#include <assert.h>
#include <set>
#include <iostream>

void test()
{
    // TEST 1
    std::unique_ptr<GraphLst> hex = Hexagone();
    std::set<std::set<u64>> maxIndSets = hex->getMaxIndSets();
    std::set<std::set<u64>> expected =
        {
            {0, 2, 4}, {1, 3, 5}};
    for (auto &set : maxIndSets)
        assert(expected.find(set) != expected.end());

    // TEST 2
    std::unique_ptr<GraphLst> meth = Methane();
    std::set<std::set<u64>> maxIndSets2 = meth->getMaxIndSets();
    std::set<u64> expected2 = {1, 2, 3, 4};
    for (auto &set : maxIndSets2)
        assert(set == expected2);
}

int main()
{

    test();

    return 0;
}