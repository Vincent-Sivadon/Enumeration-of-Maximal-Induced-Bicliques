#include <assert.h>

#include "graphesMat.hpp"

int main() {
    // First test
    std::vector<u64> dist = {0, 1, 2, 3};
    std::vector<bool> visited = {true, true, false, false};
    assert(2 == GM::minDist(dist,visited));

    // Second test
    std::vector<u64> dist2 = {4, 3, 2, 3};
    std::vector<bool> visited2 = {false, true, true, true};
    assert(0 == GM::minDist(dist2,visited2));

    return 0;
}