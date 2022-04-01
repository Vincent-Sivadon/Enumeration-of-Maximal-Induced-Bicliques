
set(CMAKE_CURRENT_INCLUDE_DIR ${INCLUDE_DIR})
add_library(Graph STATIC 
    graphLst.cpp ${INCLUDE_DIR}/grapheLst.hpp
    graphMat.cpp ${INCLUDE_DIR}/grapheMat.hpp
    StructGraph.cpp ${INCLUDE_DIR}/StructGraph.hpp
    suffixTree.cpp ${INCLUDE_DIR}/suffixTree.hpp
    visualisation.cpp
)
target_link_libraries(Graph PUBLIC SDL2 OpenMP::OpenMP_CXX)
target_include_directories(Graph PUBLIC ${CMAKE_CURRENT_INCLUDE_DIR})
