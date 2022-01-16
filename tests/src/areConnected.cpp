#include <assert.h>

#include "graphes.hpp"

template <typename T>
void test()
{
    Graph<T> h2o = H2O<T>();
    Graph<T> methane = Methane<T>();

    std::cout << h2o.areConnected(0,1) << std::endl;
    assert(true  == h2o.areConnected(0, 1));
    assert(true  == h2o.areConnected(0, 2));
    assert(false == h2o.areConnected(2, 1));

    assert(true  == methane.areConnected(0, 1));
    assert(true  == methane.areConnected(0, 3));
    assert(false == methane.areConnected(2, 4));
}

// Test de la fonction areConnected (du struct Graph)
int main() {
    // Lance les tests version matrice
    test<Mat>();

    // Lance les tests version liste
    test<Lst>();


   return 0;
}