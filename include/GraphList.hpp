#pragma once

#include "Graph.hpp"

/* ============================== POUR UNE LISTE D'ADJACENCE
 * ============================== */

class GraphList : public Graph {
public:
  /* =========== MEMBRES =========== */
  std::map<u64, std::set<u64>> adj;

  GraphList(u64 n) : Graph(n) {}

  ~GraphList() override = default;

  /* ======== CONNECTIONS ENTRE SOMMETS ======== */
  void connect(u64 i, u64 j) override;
  bool areConnected(u64 i, u64 j) override;
  
  void disconnect(u64 i,
                  u64 j) override;   // supprimer le lien entre deux sommets i et j


  /* =========== VISUALISATION =========== */
  void print() const override;

  static GraphList random(u64 N);
  std::vector<u64> findDegrees() override;
  void deleteVertex(u64 i) override;
  void findMinDegree(u64 &vertexMinDeg, u64 &minDeg) override;
  bool isGraphEmpty() override;
  void degenOrder(std::vector<u64> &orderedVertices) override;

  void changeToComplementary() override;
  std::set<std::set<u64>> getBicliques_ALGO_2() override;

  bool isClique(std::set<u64> &edgeSets) override;                       // Vérifie si l'ensemble donné en parametre est bien un clique ou pas
  u64 ChooseMyPivot(std::set<u64> &CAND, std::set<u64> &SUB) override;   // Choisir un pivot parmi
  // les sommet éligible afin de
  // minimiser le nombre de sommet à axplorer pendant
  // la recherche des cliques maximales

  void expandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q, std::set<std::set<u64>> &stockCliques) override;   // Procédure
  // récursive de recherche par arbre couvrant des
  // cliques

  void getAllMaxCliques(std::set<u64> vertices, std::set<std::set<u64>> &cliques) override;   // Calcul effectif des cliques maximales
protected:
  std::unique_ptr<Graph> make(u64 n) override;
};