#include <assert.h>

#include "graphes.hpp"

template <typename T>
void test()
{
    Graph<T> h2o = H2O<T>();
    Graph<T> hex = Hexagone<T>();
    hex.connect(0, 3);
    hex.connect(4, 2);

    // TEST 1
    Graph<T> subgraph_h2o0 = h2o.genSubgraph(0);
    u64 N = subgraph_h2o0.N;

    for (u64 i = 0; i < subgraph_h2o0.N; i++)
        for (u64 j = 0; j < subgraph_h2o0.N; j++)
            assert(false == subgraph_h2o0.areConnected(i - 0, j - 0));

    // TEST 2
    Graph subgraph_hex0 = hex.genSubgraph(0);

    assert(subgraph_hex0.areConnected(2 - 0, 4 - 0));
    assert(subgraph_hex0.areConnected(2 - 0, 5 - 0));
    assert(subgraph_hex0.areConnected(1 - 0, 4 - 0));

    assert(!subgraph_hex0.areConnected(1 - 0, 2 - 0));
    assert(!subgraph_hex0.areConnected(1 - 0, 5 - 0));

    assert(!subgraph_hex0.areConnected(4 - 0, 5 - 0));
}

int main()
{
    // Lance les tests version matrice
    test<Mat>();

    // Lance les tests version liste
    test<Lst>();

    return 0;
}