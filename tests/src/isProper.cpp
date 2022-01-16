#include <assert.h>

#include "graphes.hpp"

template <typename T>
void test() {
    Graph<T> hex = Hexagone<T>();
    Graph<T> methane = Methane<T>();
    
    // TEST 1
    assert(false == methane.isProper({1,2,3,4}));
    assert(true == methane.isProper({0,1,4}));
    assert(true ==methane.isProper({0,1,3}));
    assert(false == methane.isProper({1,2,3}));
    
    // TEST 2
    assert(false == hex.isProper({0,4,2}));
    assert(true == hex.isProper({1,2,3,4,5}));
}

int main() {
    // Lance les tests version matrice
    test<Mat>();

    // Lance les tests version liste
    test<Lst>();


   return 0;
}