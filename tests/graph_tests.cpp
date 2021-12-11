#include <stdio.h>
#include <assert.h>

#include "graph.hpp"

void test_areConnected() {
    Graph h2o = H2O();
    Graph methane = Methane();

    assert(true  == h2o.areConnected(0, 1));
    assert(true  == h2o.areConnected(0, 2));
    assert(false == h2o.areConnected(2, 1));

    assert(true  == methane.areConnected(0, 1));
    assert(true  == methane.areConnected(0, 3));
    assert(false == methane.areConnected(2, 4));
}

int main() {
    test_areConnected();

    std::cout << "\n##########################\n### GRAPH TESTS PASSED ###\n##########################\n" << std::endl;
    return 0;
}