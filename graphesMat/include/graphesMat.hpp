/*
    - Contient la structure Graph.
    - Cette version représente le graphe avec une matrice d'adjacence "adj"
    - La librairie utilise le namespace GM pour Graphe Matrice

*/

#pragma once

#include <vector>
#include <stdlib.h>
#include <set>
#include <map>

typedef unsigned long long u64;

namespace GM {
    

/* =========================== REPRESENTATION D'UN GRAPHE =========================== */
struct Graph {
    /* ========================= MEMBRE PRINCIPAL ========================= */
    std::vector<int> adj;   // Liste d'adjacence du graphe
    u64 N;                  // Nombre de Sommets

    // CONSTRUCTEUR
    Graph(u64 N) : N(N) {adj.resize(N*N) ;}


    /* ===================== CONNECTIONS ENTRE SOMMETS ===================== */
    void connect(u64 i, u64 j);      // Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)    
    bool areConnected(u64 i, u64 j); // Retourne un booléen indiquant si les sommets i et j sont connectés


    /* =========================== VISUALISATION =========================== */
    void print(); // Affiche le graphe dans le terminal (à des fins de debug)
    void draw(); // dessine le graphe à l'écran

    
    /* =============================== SETS =============================== */
    bool isProper(std::set<u64> set);                       // Retourn un booléen indiquant si un set est propre par rapport au graphe
    bool isConnectedToSet(u64 vertex, std::set<u64> set);   // Indique si vertex est connecté au set
    void getIndSets(std::set<std::set<u64>>& IndSets, std::set<u64>& tmpSet, u64 i); 
                                                            // Enumère tout les sets indépendants du graphe
    std::set<std::set<u64>> getMaxIndSets();                // Eumère tout les sets indépendants maximaux


    /* ============================= UTILITAIRE ============================= */
    std::vector<u64> shortestPaths(u64 src); // Donne la longueur du plus court chemin depuis src pour chaque sommet


    /* ======================== PROCEDURE DE L'ARTICLE ======================== */
    Graph genSubgraph(u64 i);               // Génère les sous-graphes d'après le papier
    std::set<std::set<u64>> getBicliques(); // Enumère tout les bicliques maximales du graphe
};

// =========================== GENERATION DE GRAPHE ===========================
Graph genRandGraph(u64 N); // Génère un graphe pour lequel chaque sommet a 50% de chance d'être connecté à un autre sommet


// =========================== GRAPHES SIMPLES ===========================
Graph H2O();        // Génère un graphe représentant une molécule de H2O
Graph Methane();    // Génère un graphe représentant une molécule de méthane
Graph Hexagone();   // Génère un graphe représentant un hexagone


// =========================== FONCTION UTILITAIRE ===========================
u64 minDist(std::vector<u64>& dist, std::vector<bool>& visited); // Get the vertex for wich the dist to src is minimal (used)
void printSets(std::set<std::set<u64>> sets); // Affiche dans le terminal un set de set


} // end namespace GM