#include <assert.h>

#include "graphes.hpp"

int main() {
    GL::Graph h2o = GL::H2O();
    GL::Graph hex = GL::Hexagone();
    hex.connect(0, 3);
    hex.connect(4, 2);

    // TEST 1   
    GL::Graph subgraph_h2o0 = h2o.genSubgraph(0);
    assert(subgraph_h2o0.adj.size() == 0);

    // TEST 2
    GL::Graph subgraph_hex0 = hex.genSubgraph(0);

    assert(subgraph_hex0.adj.size() == 4);
    assert(subgraph_hex0.areConnected(2, 4));
    assert(subgraph_hex0.areConnected(2, 5));
    assert(subgraph_hex0.areConnected(1, 4));

    assert(!subgraph_hex0.areConnected(1, 2));
    assert(!subgraph_hex0.areConnected(1, 5));

    assert(!subgraph_hex0.areConnected(4, 5));

    return 0;
}