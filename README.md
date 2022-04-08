# Enumeration de bicliques maximales d'un gaphe

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
* draw    : dessine un graph avec un blicique coloré
* genPerf : génère les données de mesures de performances dans data/perf.dat   
          : taille du graphe maximale prise à 50 par défaut, mais est spécifiable par : ./genPerf [Taille Maximale]
## Liste des macros
Taper les commandes suivantes pour leur effet:  
* make plot   : génère l'image perf.png et l'affiche  
* gtest       : execute tout les tests du projet  
* make clean  : supprime les executables  


# Structure du projet
La hiérarchie est la suivante :
* graphes : librairie de manipulation de graphe
    * include :
        * graphes.hpp       : interface de la structure Graph
        * graphesList.hpp   : implémentation de graphes sous forme de liste
        * graphesMat.hpp    : implémentation de graphes sous forme de matrice d'adjacence
        * suffixTree.hpp    : header de la structure d'arbre de suffix
        * visualisation.hpp : contient l'implémentation de Graph::draw()
   
* src :
         implémentation de l'arbre de suffix, de la visualisation ainsi que de la structure des graphes
* include : 
        contient toutes les librairies
* tests : 
    * graph : contient les tests de chaque fonction
* plot  : contient les scripts et données relatifs au plot
* apps  : contient draw.cpp et genperf.cpp


# Utilisation de la librairie
* Générer un graphe :
    * aléatoirement :
        * Forme Liste d'Adjacence   : ̀`GraphList g = random(Taille)`
        * Forme Matrice d'Adjacence : ̀`GraphMat g = random(Taille)`
    * prédéfini     :
        * Molécule de Méthane  : `Graph<GraphList> g = Méthane<GraphList>();`
* Manipulation d'un graphe :
    * Obtenir ses bicliques maximales : `std::set<std::set<u64>> bicliques = g.getBicliques()`
