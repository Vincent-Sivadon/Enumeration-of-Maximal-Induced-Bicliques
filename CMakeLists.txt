cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(
  MaxBicliqueEnumeration
  VERSION 0.1.0
  LANGUAGES CXX)

# Find dependencies
find_package(OpenMP REQUIRED)
find_package(SDL2 REQUIRED)
find_package(MPI)
if (MPI_FOUND)
else (MPI_FOUND)
  set(MPI_CXX_COMPILER /usr/local/mpich-3.4.1/bin/mpicc)
  find_package(MPI REQUIRED)
endif (MPI_FOUND)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Liste des fichiers sources
file(GLOB SRCS "src/*.cpp")
file(GLOB HDRS "include/*.cpp")

add_library(Graph SHARED ${SRCS} ${HDRS})
target_link_libraries(Graph PUBLIC OpenMP::OpenMP_CXX MPI::MPI_CXX)
target_include_directories(Graph PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(Graph PUBLIC -Ofast)


add_subdirectory(extern)

# Build la librairie "graphes"
add_subdirectory(apps)

enable_testing()
# add_subdirectory(test)

# "make plot" va afficher le graphe des perfs
# add_custom_target(plot COMMAND sh ../plot/plot.sh)
