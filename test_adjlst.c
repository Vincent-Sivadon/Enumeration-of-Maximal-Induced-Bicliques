#include <stdint.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#include "adjlst.h"

static void test_checkEdges ( void **state )
{
  Graph* graph1 = H2O();
  Graph* graph2 = Methane();

  assert_int_equal(1, checkEdge(graph1, 0,1));
  assert_int_equal(1, checkEdge(graph1, 0,2));
  assert_int_equal(0, checkEdge(graph1, 2,1));

  assert_int_equal(1, checkEdge(graph2, 0,1));
  assert_int_equal(1, checkEdge(graph2, 0,3));
  assert_int_equal(0, checkEdge(graph2, 2,4));

}

static void test_minDist ( void **state )
{
  // First test
  int dist[4]    = {0    , 1    , 2   , 3   };
  bool visited[4] = {true, true, false, false};
  assert_int_equal(2 , minDist(dist,visited,4));

  // Second test
  int dist2[4]    = {4    , 3    , 2   , 3   };
  bool visited2[4] = {false, true, true, true};
  assert_int_equal(0 , minDist(dist2,visited2,4));
}

//
static void test_dijkstra ( void **state )
{
  //
  Graph* graph = Methane();
  Graph* graph2 = H2O();

  // TEST 1
  int* dist       = dijkstra(graph, 1);
  int expected[5] = {1, 0, 2, 2, 2};
  for(int i=0 ; i<5 ; i++) { assert_int_equal(dist[i], expected[i]);}

  // TEST 2
  int* dist2      = dijkstra(graph2, 1);
  int expected2[3] = {1, 0, 2};
  for(int i=0 ; i<3 ; i++) { assert_int_equal(dist2[i], expected2[i]);}

}


int main(void) {
  int result = 0;
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_checkEdges),
      cmocka_unit_test(test_minDist),
      cmocka_unit_test(test_dijkstra),
  };
  result |= cmocka_run_group_tests_name("Adjacency List", tests, NULL, NULL);

  return result;
}