#include <assert.h>

#include "graphes.hpp"
#include "../graph_tests.hpp"

//test of isProper function
void isProperTests() {
    Graph hex = Hexagone();
    Graph methane = Methane();
    
    // TEST 1
    assert(false == methane.isProper({1,2,3,4}));
    assert(true == methane.isProper({0,1,4}));
    assert(true ==methane.isProper({0,1,3}));
    assert(false == methane.isProper({1,2,3}));
    
    // TEST 2
    assert(false == hex.isProper({0,4,2}));
    assert(true == hex.isProper({1,2,3,4,5}));
}