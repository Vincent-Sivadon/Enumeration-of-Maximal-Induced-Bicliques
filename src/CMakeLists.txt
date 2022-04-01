
set(CMAKE_CURRENT_INCLUDE_DIR ${INCLUDE_DIR})
add_library(Graph STATIC 
    GraphList.cpp ${INCLUDE_DIR}/GraphList.hpp
    GraphMat.cpp ${INCLUDE_DIR}/GraphMat.hpp
    Graph.cpp ${INCLUDE_DIR}/Graph.hpp
    SuffixTree.cpp ${INCLUDE_DIR}/SuffixTree.hpp
    Visualisation.cpp
)

target_link_libraries(Graph PUBLIC SDL2 OpenMP::OpenMP_CXX)
target_include_directories(Graph PUBLIC ${CMAKE_CURRENT_INCLUDE_DIR})
