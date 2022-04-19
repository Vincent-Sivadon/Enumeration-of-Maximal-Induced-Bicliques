/*
    - Contient l'interface pour la structure d'un graphe représenté par liste
   d'adjacence ou matrice
*/

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <stdbool.h>
#include <stdlib.h>
#include <utility>
#include <vector>

#define INF 0x3f3f3f3f

#include "SuffixTree.hpp"

typedef unsigned long long u64;

typedef struct vertexMin {
  int degree;
  int vertex;
} vertexMin;

class Graph {
public:
  Graph(u64 N) : N(N){};

  /* ============================= GRAPHES SIMPLES =============================
   */

  // Génère un graphe représentant une molécule de H2O
  template<typename T>
  static std::unique_ptr<T> makeH2O() {
    auto res = std::make_unique<T>(3);

    res->connect(0, 1);
    res->connect(0, 2);

    return res;
  }

  // Génère un graphe représentant une molécule de méthane
  template<typename T>
  static std::unique_ptr<T> makeMethane() {
    auto res = std::make_unique<T>(5);

    res->connect(0, 1);
    res->connect(0, 2);
    res->connect(0, 3);
    res->connect(0, 4);

    return res;
  }

  // Génère un graphe représentant un hexagone
  template<typename T>
  static std::unique_ptr<T> makeHexagone() {
    auto res = std::make_unique<T>(6);

    res->connect(0, 1);
    res->connect(1, 2);
    res->connect(2, 3);
    res->connect(3, 4);
    res->connect(4, 5);
    res->connect(5, 0);

    return res;
  }

  /* ======== CONNECTIONS ENTRE SOMMETS ======== */
  virtual void connect(u64 i,
                       u64 j) = 0;   // Crée un lien entre deux sommets i et j
                                     // (lors de la construction d'un graphe)
  virtual bool areConnected(u64 i,
                            u64 j) = 0;   // Retourne un booléen indiquant si les
                                          // sommets i et j sont connectés
  virtual std::vector<int>
  verticesdegrees() const = 0;   // Permet de connaitre Le degré de chaque sommet dans le graphe

  virtual void disconnect(u64 i, u64 j) = 0;   // supprimer le lien entre deux sommets i et j

  /* ================ SETS ================ */
  bool isProper(std::set<u64> set);   // Retourne un booléen indiquant si un set
                                      // est propre par rapport au graphe
  virtual bool isConnectedToSet(u64 vertex,
                                std::set<u64> set);   // Indique si un vertex est connecté au set

  virtual void getIndSets(std::set<std::set<u64>> &IndSets, std::set<u64> &tmpSet,
                          u64 i);   // Enumère tous les sets indépendants du graphe

  virtual std::set<std::set<u64>>
  getMaxIndSets(std::set<std::set<u64>> &IndSets,
                std::set<u64> &tmpSet);   // Enumère tous les sets indépendants maximaux

  /* =========== VISUALISATION =========== */
  virtual void print() const = 0;   // Affiche le graphe dans le terminal (à des fins de debug)
  void draw();                      // Dessine le graphe à  l'écran
  void drawBiclique(std::set<u64> biclique);

  /* =========== UTILITAIRE =========== */
  std::vector<u64> shortestPaths(u64 src);   // Donne la longueur du plus court chemin depuis src
                                             // pour chaque sommet
  bool isViableBiclique(std::set<u64> &X, std::set<u64> &Y,
                        u64 i);   // From the 2 sets of an original biclique,
                                  // indicates if by adding i, biclique is still viable
  bool isBicliqueMaximale(const std::set<u64> &biclique);   // Indicates if a biclique is maximale
                                                            // regarding the graph

  /* =========== PROCEDURE DE L'ARTICLE =========== */
  virtual std::unique_ptr<Graph> genSubgraph(u64 i);   // Génère les sous-graphes Gi de l'algo
                                                       // (sigma contiendra l'ordre des sommets)
  virtual std::vector<std::unique_ptr<Graph>>
  genSubgraphGik(u64 i);   // Génère les sous-graphes Gik à partir d'un graphe Gi donné

  std::set<std::set<u64>> getBicliques();   // Enumère tout les bicliques maximales du graphe
  std::set<std::set<u64>> getBicliquesParallel();   // version parallèle OpenMP
  virtual std::vector<u64> findDegrees() = 0; // Permet de connaitre le degré de tous les sommet à un instant donné
  virtual void deleteVertex(u64 i) = 0;       //   supprime le sommet dont l'identifiant est passer en argument du graphe
  virtual void findMinDegree(u64 &vertexMinDeg, u64 &minDeg) = 0; // Permet de trouver le sommet courant de degré minimal dans le graphe
  virtual void degenOrder(std::vector<u64> &orderedVertices) = 0; // permet d'avoir l'ordre de dégénérescence dans le graphe

  void randomize();   // Permet de génerer aléatoirement un graphe

  u64 getSize() { return N; }

protected:
  u64 N;
  virtual std::unique_ptr<Graph> make(u64 n) = 0;
};

/* ============================= FONCTION UTILITAIRE
 * ============================= */
u64 minDist(std::vector<u64> &dist,
            std::vector<bool> &visited);        // Donne le vertex pour lequel la
                                                // distance à la source est minimal
void printSets(std::set<std::set<u64>> sets);   // Affiche dans le terminal un set de set