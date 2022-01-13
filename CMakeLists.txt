#[[
    Pour build le projet :
        mkdir build
        cd build
        cmake ..
    
    Pour générer les executables :
        make EXECUTABLE
    
    Les EXECUTABLES sont :
        draw    : dessine un hexagone à l'écran
        genPerf : génère les données de mesures de performances dans data/perf.dat 

    Autre :
        make plot   : génère l'image perf.png et l'affiche
        ctest       : execute tout les tests du projet
        clean       : nettoie le répertoire build
]]


cmake_minimum_required(VERSION 3.12)
project(MaxBicliqueEnumeration VERSION 0.1.0) 

# Build la librairie "graphes"
add_subdirectory(graphes)

# Génère les tests
add_subdirectory(tests)

# Import des librairies
find_package(OpenMP REQUIRED)
find_package(SDL2 REQUIRED)


# Génère les mesures de performances moyénnées de la fonction getBicliques pour des tailles variables
add_executable(genPerf genPerf.cpp)
target_link_libraries(genPerf graphes OpenMP::OpenMP_CXX SDL2)
target_compile_options(genPerf PUBLIC -std=c++17)
add_custom_command(TARGET genPerf POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta
                    "============== EXECUTABLE genPerf CREE DANS LE REPERTOIRE build"
                    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta
                    "============== génère les mesures de performances moyénnées de la fonction getBicliques pour des tailles variables")

# Executable qui dessine un hexagone à l'écran
add_executable(draw draw.cpp)
target_link_libraries(draw graphes OpenMP::OpenMP_CXX SDL2)
target_compile_options(draw PUBLIC -std=c++17)
add_custom_command(TARGET draw POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta
                    "============== EXECUTABLE draw CREE DANS LE REPERTOIRE build"
                    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta
                    "============== dessine un hexagone à l écran")


# "ctest" va lancer tout les tests
enable_testing()
add_test(Tests tests/tests)

# "make plot" va afficher le graphe des perfs
add_custom_target(plot)
add_custom_command(TARGET plot
    COMMAND sh ../plot.sh
    )