# Enumeration de bicliques maximales d'un gaphe

![Graph](Graph.gif "Graph")

# Utilisation
* Création d'un graphe :
    * A partir d'un fichier :
        `Graph g; g.InitFromFile(filename)`
    * Aléatoirement :
        `Graph g(N); g.Randomize();`
    * Prédéfini     :
        * Graphe en forme d'hexagone  : `Graph g; g.MakeHexagone()`
* Enumération des bicliques :
    * Algorithm 1 : `set<set<u64>> bicliques = g.GetBicliques()`
    * Algorithm 2 : `set<set<u64>> bicliques = g.GetBicliques2()`
* Utilitaires :
    * Ecriture des liens dans un fichier : `g.WriteToFile(filename)`
    * Affichage dans le terminal : `g.Print()`


# Build
Pour constuire le projet :  
```
    mkdir build  
    cd build  
    cmake ..  
    make
```
Chaque fichier dans le sous-dossier `apps` donnera un executable du même nom dans le sous-dossier `build`.  


# Structure du répertoire
L'ensemble des fonctionnalités est réuni dans une librairie `Graph`, dont les fichiers sont dans les sous-dossiers `include` et `src`.  
Les autres répertoires sont :
* `apps` : contient des fichiers sources utilisant la bibliothèque `Graph`
* `test` : tests de la librairie
* `networks` : réseaux en .csv
* `data` : relatif au mesures

