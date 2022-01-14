#include <assert.h>

#include "graphesMat.hpp"

int main() {
    GM::Graph h2o = GM::H2O();
    GM::Graph hex = GM::Hexagone();
    hex.connect(0, 3);
    hex.connect(4, 2);

    // TEST 1   
    GM::Graph subgraph_h2o0 = h2o.genSubgraph(0);
    u64 N = subgraph_h2o0.N;
    for(u64 i=0 ; i<N ; i++)
        for(u64 j=0 ; j<N ; j++)
            assert(subgraph_h2o0.adj[i*N + j] == 0);

    // TEST 2
    GM::Graph subgraph_hex0 = hex.genSubgraph(0);

    assert(subgraph_hex0.areConnected(2, 4));
    assert(subgraph_hex0.areConnected(2, 5));
    assert(subgraph_hex0.areConnected(1, 4));

    assert(!subgraph_hex0.areConnected(1, 2));
    assert(!subgraph_hex0.areConnected(1, 5));

    assert(!subgraph_hex0.areConnected(4, 5));

    return 0;
}