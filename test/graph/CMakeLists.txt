
add_executable(GraphLst_test GraphLst_test.cpp)
target_link_libraries(GraphLst_test Graph gtest_main)

include(GoogleTest)
gtest_discover_tests(GraphLst_test)