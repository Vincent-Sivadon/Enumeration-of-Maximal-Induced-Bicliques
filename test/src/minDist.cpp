#include <assert.h>

void test()
{
    // First test
    std::vector<u64> dist = {0, 1, 2, 3};
    std::vector<bool> visited = {true, true, false, false};
    assert(2 == minDist(dist, visited));

    // Second test
    std::vector<u64> dist2 = {4, 3, 2, 3};
    std::vector<bool> visited2 = {false, true, true, true};
    assert(0 == minDist(dist2, visited2));
}

int main()
{

    test();

    return 0;
}