#include <Graph.hpp>
#include <gtest/gtest.h>

TEST(Graph_Tests, GetBiclicques) {
    Graph g;
    g.MakeHexagone();
    
    std::set<std::set<u64>> bicliques = g.GetBicliques();
    std::set<std::set<u64>> expected = {
      {0, 1, 2},
      {1, 2, 3},
      {2, 3, 4},
      {3, 4, 5},
      {0, 4, 5},
      {0, 1, 5}
    };
}