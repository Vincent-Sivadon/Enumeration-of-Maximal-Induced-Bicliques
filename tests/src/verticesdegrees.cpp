#include <assert.h>

#include "graphes.hpp"

template <typename T>
void test()
{
    Graph<T> h2o = H2O<T>();
    Graph<T> methane = Methane<T>();

   vertexMin s;
   s.vertex = 1;
   s.degree = 1;

    assert(1 == h2o.findMinVertex().vertex );
    assert(1 == h2o.findMinVertex().degree);


    assert( 1 == methane.findMinVertex().degree);
    assert( 1 == methane.findMinVertex().vertex);

}

// Test de la fonction areConnected (du struct Graph)
int main()
{
    // Lance les tests version matrice
    test<Mat>();

    // Lance les tests version liste
    test<Lst>();

    return 0;
}