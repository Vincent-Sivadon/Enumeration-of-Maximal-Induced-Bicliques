#pragma once

#include <vector>
#include <stdlib.h>
#include <set>
#include <map>

typedef unsigned long long u64;

namespace GM {
    

// Structure représentatant un Graphe
struct Graph {
    std::vector<int> adj;   // Liste d'adjacence du graphe
    u64 N;                  // Nombre de Sommets

    // Constructeur
    Graph(u64 N) : N(N) {adj.resize(N*N) ;}

    // Affiche le graphe dans le terminal (à des fins de debug)
    void print();

    // dessine le graphe à l'écran
    void draw();

    // Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
    void connect(u64 i, u64 j);

    // Retourne un booléen indiquant si les sommets i et j sont connectés
    bool areConnected(u64 i, u64 j);

    // Retourn un booléen indiquant si un set est propre par rapport au graphe
    bool isProper(std::set<u64> set);

    // Donne la longueur du plus court chemin depuis src pour chaque sommet
    std::vector<u64> shortestPaths(u64 src);

    // Génère les sous-graphes d'après le papier
    Graph genSubgraph(u64 i);

    // Indique si vertex est connecté au set
    bool isConnectedToSet(u64 vertex, std::set<u64> set);

    // Enumère tout les sets indépendants maximaux du graphe
    void getIndSets(std::set<std::set<u64>>& IndSets, std::set<u64>& tmpSet, u64 i);
    std::set<std::set<u64>> getMaxIndSets();

    // Enumère tout les bicliques maximales du graphe
    std::set<std::set<u64>> getBicliques();

};

// Génère un graphe pour lequel chaque sommet a 50% de chance d'être connecté à un autre sommet
Graph genRandGraph(u64 N);

// Génère un graphe qui représente une molecule d'eau (à des fins de tests majoritairement)
Graph H2O();

// Génère un graphe qui représente une molecule de méthane (à des fins de tests majoritairement)
Graph Methane();

// Génère un graphe qui représente une molecule en forme d'hexagone (à des fins de tests majoritairement)
Graph Hexagone();

// Get the vertex for wich the dist to src is minimal (used)
u64 minDist(std::vector<u64>& dist, std::vector<bool>& visited);

// Affiche dans le terminal un set de set
void printSets(std::set<std::set<u64>> sets);


} // end namespace GM