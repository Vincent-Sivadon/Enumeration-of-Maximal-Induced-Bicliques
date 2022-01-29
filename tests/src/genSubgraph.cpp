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
    std::map<u64, u64> sigma;
    Graph<T> subgraph_h2o0 = h2o.genSubgraph(0, sigma);
    u64 N = subgraph_h2o0.N;

    for (u64 i = 0; i < subgraph_h2o0.N; i++)
        for (u64 j = 0; j < subgraph_h2o0.N; j++)
            assert(false == subgraph_h2o0.areConnected(sigma[i], sigma[j]));

    // TEST 2
    std::map<u64, u64> sigma2;
    Graph subgraph_hex0 = hex.genSubgraph(0, sigma2);

    assert(subgraph_hex0.areConnected(sigma2[2], sigma2[4]));
    assert(subgraph_hex0.areConnected(sigma2[2], sigma2[5]));
    assert(subgraph_hex0.areConnected(sigma2[1], sigma2[4]));

    assert(!subgraph_hex0.areConnected(sigma2[1], sigma2[2]));
    assert(!subgraph_hex0.areConnected(sigma2[1], sigma2[5]));

    assert(!subgraph_hex0.areConnected(sigma2[4], sigma2[5]));
}

int main()
{
    // Lance les tests version matrice
    test<Mat>();

    // Lance les tests version liste
    test<Lst>();

    return 0;
}