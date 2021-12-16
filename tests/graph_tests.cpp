#include <iostream>
#include <assert.h>
#include <set>

# define INF 0x3f3f3f3f

#include "graph.hpp"

void test_areConnected() {
    Graph h2o = H2O();
    Graph methane = Methane();

    assert(true  == h2o.areConnected(0, 1));
    assert(true  == h2o.areConnected(0, 2));
    assert(false == h2o.areConnected(2, 1));

    assert(true  == methane.areConnected(0, 1));
    assert(true  == methane.areConnected(0, 3));
    assert(false == methane.areConnected(2, 4));
}

void test_isProper() {
    Graph h2o = H2O();
    Graph methane = Methane();
    std::set<int> s1 = {0,1};
    std::set<int> s2 = {0,1,2};
    std::set<int> s3 = {0,3};
    std::set<int> s4 = {0,1,2,3,4};

    assert(true == h2o.isProper(s1));
    assert(false == h2o.isProper(s2));
    
    assert(true == methane.isProper(s3));
    assert(false == methane.isProper(s4));
}

void test_minDist() {
    // First test
    std::vector<int> dist = {0, 1, 2, 3};
    std::vector<bool> visited = {true, true, false, false};
    assert(2 == minDist(dist,visited));

    // Second test
    std::vector<int> dist2 = {4, 3, 2, 3};
    std::vector<bool> visited2 = {false, true, true, true};
    assert(0 == minDist(dist2,visited2));
}

void test_shortestPaths() {
    Graph methane = Methane();
    Graph h2o = H2O();
    Graph hex = Hexagone();

    // TEST 1
    std::vector<int> dist = methane.shortestPaths(1);
    std::vector<int> expected = {1, 0, 2, 2, 2};
    assert(dist == expected);

    // TEST 2
    std::vector<int> dist2 = h2o.shortestPaths(1);
    std::vector<int> expected2 = {1, 0, 2};
    assert(dist2 == expected2);

    // TEST 3
    std::vector<int> dist3 = hex.shortestPaths(0);
    std::vector<int> expected3 = {0, 1, 2, INF, 2, 1};
    assert(dist3 == expected3);
}

void test_genSubgraph() {
    Graph h2o = H2O();
    Graph hex = Hexagone();
    hex.connect(0, 3);
    hex.connect(4, 2);

    // TEST 1
    /*
    Graph subgraph_h2o0 = h2o.genSubgraph(0);
    assert(subgraph_h2o0.adj.size() == 0);
*/
    // TEST 2
    Graph subgraph_hex0 = hex.genSubgraph(0);

    assert(subgraph_hex0.adj.size() == 4);
    assert(subgraph_hex0.areConnected(2, 4));
    assert(subgraph_hex0.areConnected(2, 5));
    assert(subgraph_hex0.areConnected(1, 4));

    assert(!subgraph_hex0.areConnected(1, 2));
    assert(!subgraph_hex0.areConnected(1, 5));

    assert(!subgraph_hex0.areConnected(4, 5));
}

void printSets(std::set<std::set<int>> sets)
{
    for(auto& set : sets) {
        for(auto& i : set) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

void test_getMaxIndSets()
{
    // TEST 1
    Graph hex = Hexagone();
    std::set<std::set<int>> maxIndSets = hex.getMaxIndSets();
    std::set<std::set<int>> expected = 
        {
            {0, 2, 4}, {1, 3, 5}
        };
    for (auto& set : maxIndSets)
        assert(expected.find(set) != expected.end());

    // TEST 2
    Graph meth = Methane();
    std::set<std::set<int>> maxIndSets2 = meth.getMaxIndSets();
    std::set<int> expected2 = {1, 2, 3, 4};
    for(auto& set : maxIndSets2)
        assert(set == expected2);
}

void test_getBicliques() {
    Graph hex = Hexagone();
    hex.connect(0, 3);
    hex.connect(4, 2);
    hex.connect(0, 2);
    std::set<std::set<int>> hex_bicliques = hex.getBicliques();
    printSets(hex_bicliques);
    /* Should have the max induced bicliques
        0 ----- 2
          -   - 
            -
          -   -
        4 ----- 3
    */

}

int main() {
    test_areConnected();
    test_isProper();
    test_minDist();
    test_shortestPaths();
    test_genSubgraph();
    //test_getMaxIndSets();
    //test_getBicliques();

    std::cout << "\n##########################\n### GRAPH TESTS PASSED ###\n##########################\n" << std::endl;
    return 0;
}