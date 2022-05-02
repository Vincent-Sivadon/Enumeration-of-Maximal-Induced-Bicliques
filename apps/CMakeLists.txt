set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(draw draw.cpp)
target_link_libraries(draw PUBLIC Graph)

add_executable(genPerf genPerf.cpp)
target_link_libraries(genPerf PUBLIC Graph)

add_executable(readFile readFile.cpp)
target_link_libraries(readFile PUBLIC Graph)

add_executable(getBicliques getBicliques.cpp)
target_link_libraries(getBicliques PUBLIC Graph)
target_compile_options(getBicliques PUBLIC -ggdb3 -Ofast)

add_executable(complementary complementary.cpp)
target_link_libraries(complementary PUBLIC Graph)

add_executable(genPerfIndSets genPerfIndSets.cpp)
target_link_libraries(genPerfIndSets PUBLIC Graph)

add_executable(bronKerbosch bronKerbosch.cpp)
target_link_libraries(bronKerbosch PUBLIC Graph)
