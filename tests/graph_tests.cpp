#include <iostream>
#include <assert.h>
#include <set>

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

void test_isProper() {
    Graph h2o = H2O();
    Graph methane = Methane();
    std::set<int> s1 = {0,1};
    std::set<int> s2 = {0,1,2};
    std::set<int> s3 = {0,3};
    std::set<int> s4 = {0,1,2,3,4};

    assert(true == h2o.isProper(s1));
    assert(false == h2o.isProper(s2));
    
    assert(true == methane.isProper(s3));
    assert(false == methane.isProper(s4));
}

int main() {
    test_areConnected();
    test_isProper();

    std::cout << "\n##########################\n### GRAPH TESTS PASSED ###\n##########################\n" << std::endl;
    return 0;
}