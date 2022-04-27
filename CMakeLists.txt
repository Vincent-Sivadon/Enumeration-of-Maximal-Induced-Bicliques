cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(
  MaxBicliqueEnumeration
  VERSION 0.1.0
  LANGUAGES CXX)

# Find dependencies
find_package(OpenMP REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(extern)

# Build la librairie "graphes"
add_subdirectory(src)
add_subdirectory(apps)

enable_testing()
add_subdirectory(test)

# "make plot" va afficher le graphe des perfs
add_custom_target(plot COMMAND sh ../plot/plot.sh)
