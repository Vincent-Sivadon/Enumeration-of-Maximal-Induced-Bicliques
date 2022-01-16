# Enumeration de bicliques maximales d'un gaphe

![adjacencyMatrix](adjacencyMatrix.png "Matrice d'Adjacence")

# Build
Pour constuire le projet :  
```
    mkdir build  
    cd build  
    cmake ..  
```
Pour construire tout les exectuables : `make`  

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


# Structure du projet
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


# Utilisation de la librairie
* Générer un graphe :
    * aléatoirement :
        * Forme Liste d'Adjacence   : ̀`Graph<Lst> g = genRandGraph<Lst>(Taille)`
        * Forme Matrice d'Adjacence : ̀`Graph<Mat> g = genRandGraph<Mat>(Taille)`
    * prédéfini     :
        * Molécule de Méthane  : `Graph<Lst> g = Méthane<Lst>();`
* Manipulation d'un graphe :
    * Obtenir ses bicliques maximales : `std::set<std::set<u64>> bicliques = g.getBicliques()`