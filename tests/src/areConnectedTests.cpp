#include <assert.h>

#include "graphes.hpp"

// Test de la fonction areConnected (du struct Graph)
int main() {
    GL::Graph h2o = GL::H2O();
    GL::Graph methane = GL::Methane();

    assert(true  == h2o.areConnected(0, 1));
    assert(true  == h2o.areConnected(0, 2));
    assert(false == h2o.areConnected(2, 1));

    assert(true  == methane.areConnected(0, 1));
    assert(true  == methane.areConnected(0, 3));
    assert(false == methane.areConnected(2, 4));

    return 0;
}

