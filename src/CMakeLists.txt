set(CMAKE_CURRENT_INCLUDE_DIR ${INCLUDE_DIR})
add_library(
  Graph STATIC
  GraphList.cpp
  ${INCLUDE_DIR}/GraphList.hpp
  GraphMat.cpp
  ${INCLUDE_DIR}/GraphMat.hpp
  Graph.cpp
  ${INCLUDE_DIR}/Graph.hpp
  Bron-Kerbosch.cpp
  Bron-Kerbosch2.cpp
  SuffixTree.cpp
  ${INCLUDE_DIR}/SuffixTree.hpp
  ReadFile.cpp
  ${INCLUDE_DIR}/ReadFile.hpp
  Visualisation.cpp)

target_link_libraries(Graph PUBLIC SDL2 OpenMP::OpenMP_CXX MPI::MPI_CXX)
target_include_directories(Graph PUBLIC ${CMAKE_CURRENT_INCLUDE_DIR})
target_compile_options(Graph PUBLIC -g)
