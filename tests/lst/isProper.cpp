#include <assert.h>

#include "graphes.hpp"

//test of isProper function
int main() {
    GL::Graph hex = GL::Hexagone();
    GL::Graph methane = GL::Methane();
    
    // TEST 1
    assert(false == methane.isProper({1,2,3,4}));
    assert(true == methane.isProper({0,1,4}));
    assert(true ==methane.isProper({0,1,3}));
    assert(false == methane.isProper({1,2,3}));
    
    // TEST 2
    assert(false == hex.isProper({0,4,2}));
    assert(true == hex.isProper({1,2,3,4,5}));

    return 0;
}