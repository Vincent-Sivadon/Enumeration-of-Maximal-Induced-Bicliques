#include <GraphList.hpp>
#include <gtest/gtest.h>

TEST(GraphLstTest, areConnected) {
  auto h2o = Graph::makeH2O<GraphList>();
  auto methane = Graph::makeMethane<GraphList>();

  assert(true == h2o->areConnected(0, 1));
  assert(true == h2o->areConnected(0, 2));
  assert(false == h2o->areConnected(2, 1));

  assert(true == methane->areConnected(0, 1));
  assert(true == methane->areConnected(0, 3));
  assert(false == methane->areConnected(2, 4));
}

TEST(GraphLstTest, genSubgraph) {
  auto h2o = Graph::makeH2O<GraphList>();

  auto hex = Graph::makeHexagone<GraphList>();

  hex->connect(0, 3);
  hex->connect(4, 2);

  // TEST 1
  auto subgraph_h2o0 = h2o->genSubgraph(0);
  u64 N = subgraph_h2o0->getSize();

  for (u64 i = 0; i < subgraph_h2o0->getSize(); i++)
    for (u64 j = 0; j < subgraph_h2o0->getSize(); j++)
      assert(false == subgraph_h2o0->areConnected(i, j));

  // TEST 2
  auto subgraph_hex0 = hex->genSubgraph(0);

  assert(subgraph_hex0->areConnected(2, 4));
  assert(subgraph_hex0->areConnected(2, 5));
  assert(subgraph_hex0->areConnected(1, 4));

  assert(!subgraph_hex0->areConnected(1, 2));
  assert(!subgraph_hex0->areConnected(1, 5));

  assert(!subgraph_hex0->areConnected(4, 5));
}

TEST(GraphLstTest, getBicliques) {
  auto hex = Graph::makeHexagone<GraphList>();

  hex->connect(0, 3);
  hex->connect(4, 2);
  hex->connect(0, 2);

  std::set<std::set<u64>> hex_bicliques = hex->getBicliques();

  std::set<std::set<u64>> expected = {{0, 1, 3, 5}, {0, 2, 4, 5}, {0, 3, 4, 5}};

  printSets(hex_bicliques);

  for (auto &set : hex_bicliques) assert(expected.find(set) != expected.end());
}

TEST(GraphLstTest, getMaxIndSets) {
  // TEST 1
  auto hex = Graph::makeHexagone<GraphList>();
  std::set<std::set<u64>> maxIndSets = hex->getMaxIndSets();
  std::set<std::set<u64>> expected = {{0, 2, 4}, {1, 3, 5}};
  for (auto &set : maxIndSets) assert(expected.find(set) != expected.end());

  // TEST 2
  auto meth = Graph::makeMethane<GraphList>();
  std::set<std::set<u64>> maxIndSets2 = meth->getMaxIndSets();
  std::set<u64> expected2 = {1, 2, 3, 4};
  for (auto &set : maxIndSets2) assert(set == expected2);
}

TEST(GraphLstTest, isProper) {
  auto hex = Graph::makeHexagone<GraphList>();
  auto methane = Graph::makeMethane<GraphList>();

  // TEST 1
  assert(false == methane->isProper({1, 2, 3, 4}));
  assert(true == methane->isProper({0, 1, 4}));
  assert(true == methane->isProper({0, 1, 3}));
  assert(false == methane->isProper({1, 2, 3}));

  // TEST 2
  assert(false == hex->isProper({0, 4, 2}));
  assert(true == hex->isProper({1, 2, 3, 4, 5}));
}

TEST(GraphLstTest, midDist) {
  // First test
  std::vector<u64> dist = {0, 1, 2, 3};
  std::vector<bool> visited = {true, true, false, false};
  assert(2 == minDist(dist, visited));

  // Second test
  std::vector<u64> dist2 = {4, 3, 2, 3};
  std::vector<bool> visited2 = {false, true, true, true};
  assert(0 == minDist(dist2, visited2));
}

TEST(GraphLstTest, Dijkstra) {
  auto methane = Graph::makeMethane<GraphList>();
  auto h2o = Graph::makeH2O<GraphList>();
  auto hex = Graph::makeHexagone<GraphList>();

  // TEST 1
  std::vector<u64> dist = methane->shortestPaths(1);
  std::vector<u64> expected = {1, 0, 2, 2, 2};
  assert(dist == expected);

  // TEST 2
  std::vector<u64> dist2 = h2o->shortestPaths(1);
  std::vector<u64> expected2 = {1, 0, 2};
  assert(dist2 == expected2);

  // TEST 3
  std::vector<u64> dist3 = hex->shortestPaths(0);
  std::vector<u64> expected3 = {0, 1, 2, INF, 2, 1};
  assert(dist3 == expected3);
}

TEST(GraphLstTest, getMaxBranches) {
  std::set<u64> set1 = {0, 2, 4};
  std::set<u64> set2 = {1, 3, 5};
  std::set<u64> set3 = {2, 3};

  Tree suffixTree;

  suffixTree.insert(set1);
  suffixTree.insert(set2);
  suffixTree.insert({0, 2});
  suffixTree.insert(set3);

  std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();
  std::set<std::set<u64>> expected = {{0, 2, 4}, {1, 3, 5}};

  for (auto &set : bicliques) assert(expected.find(set) != expected.end());
}
