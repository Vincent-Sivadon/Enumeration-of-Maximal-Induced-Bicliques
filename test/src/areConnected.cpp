#include <assert.h>

void test()
{
    std::unique_ptr<GraphLst> h2o = H2O();

    std::unique_ptr<GraphLst> methane = Methane();

    assert(true == h2o->areConnected(0, 1));
    assert(true == h2o->areConnected(0, 2));
    assert(false == h2o->areConnected(2, 1));

    assert(true == methane->areConnected(0, 1));
    assert(true == methane->areConnected(0, 3));
    assert(false == methane->areConnected(2, 4));
}

// Test de la fonction areConnected (du struct Graph)
int main()
{

    test();

    return 0;
}