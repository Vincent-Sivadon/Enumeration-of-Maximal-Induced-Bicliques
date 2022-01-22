#include <assert.h>

// Nombre Entier Maximal
#define INF 0x3f3f3f3f

#include "graphes.hpp"

template <typename T>
void test()
{
    Graph<T> methane = Methane<T>();
    Graph<T> h2o = H2O<T>();
    Graph<T> hex = Hexagone<T>();

    // TEST 1
    std::vector<u64> dist = methane.shortestPaths(1);
    std::vector<u64> expected = {1, 0, 2, 2, 2};
    assert(dist == expected);

    // TEST 2
    std::vector<u64> dist2 = h2o.shortestPaths(1);
    std::vector<u64> expected2 = {1, 0, 2};
    assert(dist2 == expected2);

    // TEST 3
    std::vector<u64> dist3 = hex.shortestPaths(0);
    std::vector<u64> expected3 = {0, 1, 2, INF, 2, 1};
    assert(dist3 == expected3);
}

int main()
{
    // Lance les tests version matrice
    test<Mat>();

    // Lance les tests version liste
    test<Lst>();

    return 0;
}