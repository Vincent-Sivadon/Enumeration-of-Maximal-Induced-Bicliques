# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(graphes)

# SDL : bibliothèque graphique 2D
find_package(SDL2 REQUIRED)

# Créé des variables avec les fichiers à compiler
file(GLOB SRCS
	"src/*.cpp"
)

file(GLOB HEADERS
	"include/*.hpp"
)

add_library(graphes STATIC ${SRCS} ${HEADERS})
target_link_libraries(graphes SDL)
target_include_directories(graphes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_options(graphes PUBLIC -std=c++17)
add_custom_command(TARGET graphes POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta
                    "============== LIBRAIRIE graphes BIEN CONSTRUITE ==============")