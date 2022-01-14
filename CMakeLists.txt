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
        clean       : supprime les executables
]]

cmake_minimum_required(VERSION 3.12)
project(MaxBicliqueEnumeration VERSION 0.1.0) 

# Build la librairie "graphes"
add_subdirectory(graphes)      # Version avec Liste d'Adjacence
add_subdirectory(graphesMat)   # Version avec Matrice d'Adjacence

# Génère les tests  : la commande "ctest" permet de lancer tout les tests
enable_testing()
add_subdirectory(tests)

# Import des librairies
find_package(OpenMP REQUIRED)
find_package(SDL2 REQUIRED)



# Génère les mesures de performances moyénnées de la fonction getBicliques pour des tailles variables
add_executable(genPerf ${CMAKE_SOURCE_DIR}/genPerf.cpp)
target_link_libraries(genPerf graphes graphesMat OpenMP::OpenMP_CXX SDL2)
target_compile_options(genPerf PUBLIC -std=c++17)


# Executable qui dessine un hexagone à l'écran
add_executable(draw ${CMAKE_SOURCE_DIR}/draw.cpp)
target_link_libraries(draw graphes OpenMP::OpenMP_CXX SDL2)
target_compile_options(draw PUBLIC -std=c++17)


# Executable qui dessine un hexagone à l'écran VERSION MATRICE D'ADJACENCE
add_executable(drawMat ${CMAKE_SOURCE_DIR}/drawMat.cpp)
target_link_libraries(drawMat graphesMat OpenMP::OpenMP_CXX SDL2)
target_compile_options(drawMat PUBLIC -std=c++17)



# "make plot" va afficher le graphe des perfs
add_custom_target(plot COMMAND sh ../plot.sh)

string(ASCII 27 ESCAPE)
message("${ESCAPE}[1;36m ============================ STRUCTURE DU PROJET ============================ ")
message("Pour build le projet :")
message("      - mkdir build")
message("      - cd build")
message("      - cmake ..")
message("      - make")
message(" Ceci aura pour effet de construire tout les executables du projet dans le nouveau répertoire -bin-")
message("")
message("Liste de tout les executables")
message("      - draw    : dessine un hexagone à l ecran")
message("      - genPerf : génère les données de mesures de performances dans data/perf.dat")
message("")
message("Liste des macro")
message("      - make plot : génère l'image perf.png et l affiche")
message("      - ctest     : execute tout les tests du projet")
message("      - clean     : supprime les executables")
message("================================================================================${ESCAPE}[0m")

