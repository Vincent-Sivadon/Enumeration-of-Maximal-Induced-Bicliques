/*
    - Contient la structure Graph.
*/

#pragma once

#include <vector>
#include <stdlib.h>
#include <set>
#include <map>
#include <memory>
#include <utility>

#define INF 0x3f3f3f3f

#include "suffixTree.hpp"
#include "adj.hpp"

typedef unsigned long long u64;

/* =========================== REPRESENTATION D'UN GRAPHE =========================== */
template <typename T>
struct Graph
{
    /* =========== MEMBRE PRINCIPAL =========== */
    std::unique_ptr<Adj> adj; // Liste ou Matrice d'adjacence du graphe
    u64 N;                    // Nombre de Sommets

    /* =========== CONSTRUCTEUR =========== */
    Graph(u64 N) : N(N) { adj = std::make_unique<T>(N); }
    Graph() { adj = std::make_unique<T>; }

    /* ======== CONNECTIONS ENTRE SOMMETS ======== */
    void connect(u64 i, u64 j) { adj->connect(i, j); }                  // Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
    bool areConnected(u64 i, u64 j) { return adj->areConnected(i, j); } // Retourne un booléen indiquant si les sommets i et j sont connectés

    /* ================ SETS ================ */
    bool isProper(std::set<u64> set);                                                // Retourn un booléen indiquant si un set est propre par rapport au graphe
    bool isConnectedToSet(u64 vertex, std::set<u64> set);                            // Indique si vertex est connecté au set
    void getIndSets(std::set<std::set<u64>> &IndSets, std::set<u64> &tmpSet, u64 i); // Enumère tout les sets indépendants du graphe
    std::set<std::set<u64>> getMaxIndSets();                                         // Eumère tout les sets indépendants maximaux
    std::set<std::set<u64>> getMaxIndSets2();
    std::set<std::set<u64>> getMaxIndSets3();


    /* ============ BRON-KERBOSCH ========== */
    //Inter and union functions for Bron Kerbosch
    std::set<u64> inter(std::set<u64> set, u64 v);           // Retourne l'intersection entre le sommet et l'ensemble de sommets entrés. 
    std::set<u64> u(std::set<u64> uni, std::set<u64> v);               // Retourne l'union des mêmes arguments. 

    // Bron Kerbosch algorithm 1
    void prepareBron();
    void bronKerbosch(std::set<u64> R, std::set<u64> P, std::set<u64> X); // Algorithme permettant de générer les ensembles indépendants maximaux. 
    std::set<std::set<u64>> cliques1; // Variabe globale permettant de stocker les ensembles maximaux indépendants. 

    // Bron Kerbosch algorithm 2
    void prepareBron2();
    void bronKerbosch2(std::set<u64> R, std::set<u64> P, std::set<u64> X); // Algorithme permettant de générer les ensembles indépendants maximaux. 
    std::set<std::set<u64>> cliques2;  // Variabe globale permettant de stocker les ensembles maximaux indépendants. 

    /* =========== VISUALISATION =========== */
    void print() { adj->print(); }; // Affiche le graphe dans le terminal (à des fins de debug)
    void draw();                    // Dessine le graphe à  l'écran
    void drawBiclique(std::set<u64> biclique);

    /* =========== UTILITAIRE =========== */
    std::vector<u64> shortestPaths(u64 src); // Donne la longueur du plus court chemin depuis src pour chaque sommet

    /* =========== PROCEDURE DE L'ARTICLE =========== */
    Graph<T> genSubgraph(u64 i);            // Génère les sous-graphes d'après le papier (sigma contiendra l'ordre des sommets)
    std::set<std::set<u64>> getBicliques(); // Enumère tout les bicliques maximales du graphe
};

/* =========================== GENERATION DE GRAPHE =========================== */
// Génère un graphe pour lequel chaque sommet a 50% de chance d'être connecté à un autre sommet
template <typename T>
Graph<T> genRandGraph(u64 N);

/* ============================= GRAPHES SIMPLES ============================= */
template <typename T>
Graph<T> H2O(); // Génère un graphe représentant une molécule de H2O
template <typename T>
Graph<T> Methane(); // Génère un graphe représentant une molécule de méthane
template <typename T>
Graph<T> Hexagone(); // Génère un graphe représentant un hexagone

/* ============================= FONCTION UTILITAIRE ============================= */
u64 minDist(std::vector<u64> &dist, std::vector<bool> &visited); // Get the vertex for wich the dist to src is minimal (used)
void printSets(std::set<std::set<u64>> sets);                    // Affiche dans le terminal un set de set

/* =========================== FICHIERS D'IMPLEMENTATION =========================== */
#include "graphesImpl.hpp"
#include "visualisation.hpp"
#include "bron-kerbosch1.hpp"
#include "bron-kerbosch2.hpp"