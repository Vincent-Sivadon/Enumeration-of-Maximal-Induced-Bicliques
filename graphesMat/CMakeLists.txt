# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(graphesMat)

# SDL : bibliothèque graphique 2D
find_package(SDL2 REQUIRED)

# Créé des variables avec les fichiers à compiler
file(GLOB SRCS
	"src/*.cpp"
)

file(GLOB HEADERS
	"include/*.hpp"
)

add_library(graphesMat STATIC ${SRCS} ${HEADERS})
target_link_libraries(graphesMat SDL)
target_include_directories(graphesMat PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_options(graphesMat PUBLIC -std=c++17)