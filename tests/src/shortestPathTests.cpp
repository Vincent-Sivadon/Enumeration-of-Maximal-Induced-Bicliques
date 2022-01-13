#include <assert.h>

// Nombre Entier Maximal
#define INF 0x3f3f3f3f

#include "graphes.hpp"
#include "../graph_tests.hpp"

void shortestPathTests() {
    Graph methane = Methane();
    Graph h2o = H2O();
    Graph hex = Hexagone();

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