#include <assert.h>

#include "graphes.hpp"
#include "../graph_tests.hpp"

// Test de la fonction areConnected (du struct Graph)
void areConnectedTests() {
    Graph h2o = H2O();
    Graph methane = Methane();

    assert(true  == h2o.areConnected(0, 1));
    assert(true  == h2o.areConnected(0, 2));
    assert(false == h2o.areConnected(2, 1));

    assert(true  == methane.areConnected(0, 1));
    assert(true  == methane.areConnected(0, 3));
    assert(false == methane.areConnected(2, 4));
}

