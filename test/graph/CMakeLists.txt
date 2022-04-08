
add_executable(GraphLst_test GraphLst_test.cpp)
add_executable(GraphMat_test GraphMat_test.cpp)
target_link_libraries(GraphLst_test Graph gtest_main)
target_link_libraries(GraphMat_test Graph gtest_main)

include(GoogleTest)
gtest_discover_tests(GraphLst_test)
gtest_discover_tests(GraphMat_test)