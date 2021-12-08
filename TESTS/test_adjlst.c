#include <stdint.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#include "../adjlst.h"

static void test_checkEdges ( void **state )
{
  Graph* graph1 = H2O();
  Graph* graph2 = Methane();

  assert_true(checkEdge(graph1, 0,1));
  assert_true(checkEdge(graph1, 0,2));
  assert_false(checkEdge(graph1, 2,1));

  assert_true(checkEdge(graph2, 0,1));
  assert_true(checkEdge(graph2, 0,3));
  assert_false(checkEdge(graph2, 2,4));

}


int main(void) {
  int result = 0;
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_checkEdges),
  };
  result |= cmocka_run_group_tests_name("Adjacency List", tests, NULL, NULL);

  return result;
}