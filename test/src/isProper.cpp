#include <assert.h>

void test()
{
    std::unique_ptr<GraphLst> hex = Hexagone();
    std::unique_ptr<GraphLst> methane = Methane();

    // TEST 1
    assert(false == methane->isProper({1, 2, 3, 4}));
    assert(true == methane->isProper({0, 1, 4}));
    assert(true == methane->isProper({0, 1, 3}));
    assert(false == methane->isProper({1, 2, 3}));

    // TEST 2
    assert(false == hex->isProper({0, 4, 2}));
    assert(true == hex->isProper({1, 2, 3, 4, 5}));
}

int main()
{
    test();

    return 0;
}