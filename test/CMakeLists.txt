
add_executable(Graph_Tests Graph_Tests.cpp)
target_link_libraries(Graph_Tests Graph gtest_main)

include(GoogleTest)
gtest_discover_tests(Graph_Tests)
