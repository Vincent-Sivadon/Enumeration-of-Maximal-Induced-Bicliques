string(ASCII 27 ESCAPE)
message("${ESCAPE}[1;36m")
message(" =================================== BUILD ===================================")
message("
    Pour constuire le projet :  
    ```
        mkdir build  
        cd build  
        cmake ..  
    ```
    Pour construire tout les exectuables : `make`  

")
message(" ======================== LISTE DES EXECUTABLES ET MACRO ========================")
message("
    ## Liste des executables
    Tout les executables vont être dans le répertoire build.  
    * draw    : dessine un hexagone à l'écran  
    * genPerf : génère les données de mesures de performances dans data/perf.dat   
            : taille du graphe maximale prise à 50 par défaut, mais est spécifiable par : ./genPerf [Taille Maximale]
    ## Liste des macros
    Taper les commandes suivantes pour leur effet:  
    * make plot   : génère l'image perf.png et l'affiche  
    * ctest       : execute tout les tests du projet  
    * make clean  : supprime les executables  
")
message(" ============================== STRUCTURE DU PROJET ==============================")
message("
    La hiérarchie est la suivante :
    * graphes : librairie de manipulation de graphe
        * include :
            * graphes.hpp       : header de la structure Graph
            * graphesImpl.hpp   : implémentation de graphes (dans un .hpp parce que c'est une structure template)
            * adj.hpp           : contient l'interface d'une liste/matrice d'adjacence
            * suffixTree.hpp    : header de la structure d'arbre de suffix
            * visualisation.hpp : contient l'implémentation de Graph::draw()
        * src :
            * suffixTree.cpp    : implémentation de l'arbre de suffix
    * tests : 
        * src : contient les tests de chaque fonction
    * data  : contient les scripts et données relatifs au plot
    * *files*.cpp : code executif faisant appel aux librairies
")
message(" ========================= UTILISATION DE LA LIBRAIRIE ==========================")
message("
    * Générer un graphe :
        * aléatoirement :
            * Forme Liste d'Adjacence   : ̀`Graph<Lst> g = genRandGraph<Lst>(Taille)`
            * Forme Matrice d'Adjacence : ̀`Graph<Mat> g = genRandGraph<Mat>(Taille)`
        * prédéfini     :
            * Molécule de Méthane  : `Graph<Lst> g = Méthane<Lst>();`
    * Manipulation d'un graphe :
        * Obtenir ses bicliques maximales : `std::set<std::set<u64>> bicliques = g.getBicliques()`
")
message("${ESCAPE}[0m")



cmake_minimum_required(VERSION 3.12)
project(MaxBicliqueEnumeration VERSION 0.1.0) 


# Build la librairie "graphes"
add_subdirectory(graphes)


# Génère les tests  : la commande "ctest" permet de lancer tout les tests
enable_testing()
add_subdirectory(tests)

# Import des librairies
find_package(OpenMP REQUIRED)
find_package(SDL2 REQUIRED)



# Génère les mesures de performances moyénnées de la fonction getBicliques pour des tailles variables
add_executable(genPerf ${CMAKE_SOURCE_DIR}/genPerf.cpp)
target_link_libraries(genPerf graphes OpenMP::OpenMP_CXX SDL2)
target_compile_options(genPerf PUBLIC -std=c++17)


# Executable qui dessine un hexagone à l'écran
add_executable(draw ${CMAKE_SOURCE_DIR}/draw.cpp)
target_link_libraries(draw graphes OpenMP::OpenMP_CXX SDL2)
target_compile_options(draw PUBLIC -std=c++17)


# "make plot" va afficher le graphe des perfs
add_custom_target(plot COMMAND sh ../data/plot.sh)
