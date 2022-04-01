#include <assert.h>

void test()
{
    std::unique_ptr<GraphLst> h2o = H2O();

    std::unique_ptr<GraphLst> hex = Hexagone();

    hex->connect(0, 3);
    hex->connect(4, 2);

    // TEST 1
    std::unique_ptr<GraphLst> subgraph_h2o0 = h2o->genSubgraph(0);
    u64 N = subgraph_h2o0->N;

    for (u64 i = 0; i < subgraph_h2o0->N; i++)
        for (u64 j = 0; j < subgraph_h2o0->N; j++)
            assert(false == subgraph_h2o0->areConnected(i, j));

    // TEST 2
    std::unique_ptr<GraphLst> subgraph_hex0 = hex->genSubgraph(0);

    assert(subgraph_hex0->areConnected(2, 4));
    assert(subgraph_hex0->areConnected(2, 5));
    assert(subgraph_hex0->areConnected(1, 4));

    assert(!subgraph_hex0->areConnected(1, 2));
    assert(!subgraph_hex0->areConnected(1, 5));

    assert(!subgraph_hex0->areConnected(4, 5));
}

int main()
{
    test();

    return 0;
}