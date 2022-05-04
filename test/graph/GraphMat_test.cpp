#include <GraphMat.hpp>
#include <gtest/gtest.h>

TEST(GraphMatTest, areConnected) {
  auto h2o = makeH2O<GraphMat>();
  auto methane = makeMethane<GraphMat>();

  assert(true == h2o->areConnected(0, 1));
  assert(true == h2o->areConnected(0, 2));
  assert(false == h2o->areConnected(2, 1));

  assert(true == methane->areConnected(0, 1));
  assert(true == methane->areConnected(0, 3));
  assert(false == methane->areConnected(2, 4));
}

TEST(GraphMatTest, genSubgraph) {
  auto h2o = makeH2O<GraphMat>();

  auto hex = makeHexagone<GraphMat>();

  hex->connect(0, 3);
  hex->connect(4, 2);

  // TEST 1
  auto subgraph_h2o0 = h2o->genSubgraph(0);
  u64 N = subgraph_h2o0->getSize();

  for (u64 i = 0; i < subgraph_h2o0->getSize(); i++)
    for (u64 j = 0; j < subgraph_h2o0->getSize(); j++) assert(false == subgraph_h2o0->areConnected(i, j));

  // TEST 2
  auto subgraph_hex0 = hex->genSubgraph(0);

  assert(subgraph_hex0->areConnected(2, 4));
  assert(subgraph_hex0->areConnected(2, 5));
  assert(subgraph_hex0->areConnected(1, 4));

  assert(!subgraph_hex0->areConnected(1, 2));
  assert(!subgraph_hex0->areConnected(1, 5));

  assert(!subgraph_hex0->areConnected(4, 5));
}

TEST(GraphMatTest, getBicliques) {
  auto hex = makeHexagone<GraphMat>();

  hex->connect(0, 3);
  hex->connect(4, 2);
  hex->connect(0, 2);

  std::set<std::set<u64>> hex_bicliques = hex->getBicliques();

  std::set<std::set<u64>> expected = {{0, 1, 3, 5}, {0, 2, 4, 5}, {0, 3, 4, 5}};

  printSets(hex_bicliques);

  for (auto &set : hex_bicliques) assert(expected.find(set) != expected.end());
}


TEST(GraphMatTest, getBicliques_ALGO_2) {
  auto hex = makeHexagone<GraphMat>();

  hex->connect(0, 3);
  hex->connect(4, 2);
  hex->connect(0, 2);

  std::set<std::set<u64>> hex_bicliques = hex->getBicliques_ALGO_2();

  std::set<std::set<u64>> expected = {{0, 1, 3, 5}, {0, 2, 4, 5}, {0, 3, 4, 5}};

  printSets(hex_bicliques);

  for (auto &set : hex_bicliques) assert(expected.find(set) != expected.end());
}

TEST(GraphMatTest, getMaxIndSets) {
  // TEST 1
  auto hex = makeHexagone<GraphMat>();
  std::set<std::set<u64>> IndSets;
  std::set<u64> tmpSet;
  std::set<std::set<u64>> maxIndSets = hex->getMaxIndSets(IndSets, tmpSet);
  std::set<std::set<u64>> expected = {{0, 2, 4}, {1, 3, 5}};
  for (auto &set : maxIndSets) assert(expected.find(set) != expected.end());

  // TEST 2
  auto meth = makeMethane<GraphMat>();
  std::set<std::set<u64>> maxIndSets2 = meth->getMaxIndSets(IndSets, tmpSet);
  std::set<u64> expected2 = {1, 2, 3, 4};
  for (auto &set : maxIndSets2) assert(set == expected2);
}

/*TEST(GraphMatTest, bronKerbosch) {
  // TEST 1
   std::set<u64> R; R.empty();
   std::set<u64> P = {1,2,3,4};
   std::set<u64> X; X.empty();

   prepareBron();
   bronKerbosch(R, P, X);
}*/


TEST(GraphMatTest, isProper) {
  auto hex = makeHexagone<GraphMat>();
  auto methane = makeMethane<GraphMat>();

  // TEST 1
  assert(false == methane->isProper({1, 2, 3, 4}));
  assert(true == methane->isProper({0, 1, 4}));
  assert(true == methane->isProper({0, 1, 3}));
  assert(false == methane->isProper({1, 2, 3}));

  // TEST 2
  assert(false == hex->isProper({0, 4, 2}));
  assert(true == hex->isProper({1, 2, 3, 4, 5}));
}

TEST(GraphMatTest, midDist) {
  // First test
  std::vector<u64> dist = {0, 1, 2, 3};
  std::vector<bool> visited = {true, true, false, false};
  assert(2 == minDist(dist, visited));

  // Second test
  std::vector<u64> dist2 = {4, 3, 2, 3};
  std::vector<bool> visited2 = {false, true, true, true};
  assert(0 == minDist(dist2, visited2));
}

TEST(GraphMatTest, Dijkstra) {
  auto methane = makeMethane<GraphMat>();
  auto h2o = makeH2O<GraphMat>();
  auto hex = makeHexagone<GraphMat>();

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

TEST(GraphMatTest, getMaxBranches) {
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

TEST(GraphMatTest, findDegrees) {
  auto methane = makeMethane<GraphMat>();
  auto hex = makeHexagone<GraphMat>();

  // TEST 1
  std::vector<u64> deg = methane->findDegrees();
  std::vector<u64> expected = {4, 1, 1, 1, 1};
  assert(deg == expected);

  // TEST 2
  std::vector<u64> deg2 = hex->findDegrees();
  std::vector<u64> expected2 = {2, 2, 2, 2, 2, 2};
  assert(deg2 == expected2);
}


TEST(GraphMatTest, minDeg) {
  auto methane = makeMethane<GraphMat>();
  auto hex = makeHexagone<GraphMat>();

  // TEST 1
  u64 vertex1, degree1;
  u64 expectedVert = 1, expectedDeg = 1;
  methane->findMinDegree(vertex1, degree1);
  assert(expectedDeg == degree1);
  assert(expectedVert == vertex1);


  // TEST 2
  u64 vertex2, degree2;
  u64 expectedVert2 = 0, expectedDeg2 = 2;
  hex->findMinDegree(vertex2, degree2);
  assert(expectedDeg2 == degree2);
  assert(expectedVert2 == vertex2);
}


TEST(GraphMatTest, degenOrder) {
  // TEST 0
  auto dgOrderGraph = makeDegenOrderGraph<GraphMat>();
  std::vector<u64> orderOfDegen;
  std::vector<u64> expectedOrderOfDegen = {0, 2, 1, 3, 4};
  dgOrderGraph->degenOrder(orderOfDegen);
  assert(orderOfDegen == expectedOrderOfDegen);

  auto methane = makeMethane<GraphMat>();
  auto h2o = makeH2O<GraphMat>();
  auto hex = makeHexagone<GraphMat>();

  // TEST 1
  std::vector<u64> orderOfDegen1(6);
  std::vector<u64> expectedOrderOfDegen1 = {0, 1, 2, 3, 4, 5};
  hex->degenOrder(orderOfDegen1);
  assert(orderOfDegen1 == expectedOrderOfDegen1);

  // TEST 2
  std::vector<u64> orderOfDegen2(3);
  std::vector<u64> expectedOrderOfDegen2 = {1, 0, 2};
  h2o->degenOrder(orderOfDegen2);
  assert(orderOfDegen2 == expectedOrderOfDegen2);

  // TEST 3
  std::vector<u64> orderOfDegen3(6);
  std::vector<u64> expectedOrderOfDegen3 = {1, 2, 3, 0, 4};
  methane->degenOrder(orderOfDegen3);

  assert(orderOfDegen3 == expectedOrderOfDegen3);
}

TEST(GraphMatTest, isClique) {
  auto methane = makeMethane<GraphMat>();
  auto hex = makeHexagone<GraphMat>();
  auto tom = makeTomitaGraph<GraphMat>();


  // TEST 1
  std::set<u64> met_set = {0, 2};
  assert(false == methane->isClique(met_set));

  // // TEST 2
  std::set<u64> tom_set1 = {0, 8, 1};
  std::set<u64> tom_set2 = {3, 7, 6, 5};

  assert(true == tom->isClique(tom_set1));
  assert(true == tom->isClique(tom_set2));
}

TEST(GraphMatTest, getCliques) {
  auto methane = makeMethane<GraphMat>();
  auto hex = makeHexagone<GraphMat>();
  auto tom = makeTomitaGraph<GraphMat>();


  // TEST 1

  std::set<std::set<u64>> get_cliques = {{0, 8, 1}, {1, 8, 2}, {3, 4, 5}, {3, 7, 2}, {3, 7, 6, 5}};
  std::set<u64> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  tom->getAllMaxCliques(vertices);
  // auto setss=  *(tom->cliques).begin();
  // assert(*(get_cliques.begin()) == *(tom->cliques).begin());

  auto it11 = get_cliques.begin();
  auto it21 = (tom->cliques).begin();
  assert(*it11 == *it21);

  // auto it12 = it11++;
  // auto it22 = it21++;
  // assert(*it12 == *it22);

  // auto it13 = it12++;
  // auto it23 = it22++;
  // assert(*it13 == *it23);

  // auto it14 = it13++;
  // auto it24 = it23++;
  // assert(*it14 == *it24);

  // auto it15 = it14++;
  // auto it25 = it24++;
  // assert(*it15 == *it25);

}