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

## Liste des macros
Taper les commandes suivantes pour leur effet:  
* make plot : génère l'image perf.png et l'affiche  
* ctest     : execute tuot les tests du projet  
* clean     : supprime les executables  


# Structure du projet
La hiérarchie est la suivante :
* graphes : librairie de manipulation de graphe par liste d'adjacence
    * include :
        * graphes.hpp       : header de la structure Graph
        * visualisation.hpp : header pour l'utilisation de la fonction drawGraph()
    * src :
        * graphes.cpp       : implémentation de la structure Graph
        * visualisation.cpp : implémentation de la simulation pour la visualisation 2D d'un graphe
* graphesMat : librairie de manipulation de graphe par matrice d'adjacence
    * include :
        * graphesMat.hpp       : header de la structure Graph
        * visualisationMat.hpp : header pour l'utilisation de la fonction drawGraph()
        * suffixTree.hpp       : header de la structure d'arbre de suffix
    * src :
        * graphesMat.cpp       : implémentation de la structure Graph
        * visualisationMat.cpp : implémentation de la simulation pour la visualisation 2D d'un graphe
        * suffixTree.cpp       : implémentation de la structure d'arbre de suffix
* tests : 
    * lst : contient les tests de la version liste
    * mat : contient les tests de la version matrice 
* data  : contient les scripts et données relatifs au plot
* *files*.cpp : code executif faisant appel aux librairies