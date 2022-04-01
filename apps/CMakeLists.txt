

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(draw draw.cpp)
target_link_libraries(draw PUBLIC Graph)

add_executable(genPerf genPerf.cpp)
target_link_libraries(genPerf PUBLIC Graph)