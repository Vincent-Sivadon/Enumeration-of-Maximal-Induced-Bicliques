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
  

  std::set<std::set<u64>> cliques2; // Variabe globale permettant de stocker les ensembles maximaux indépendants.  
  void bronKerbosch2(std::set<u64>& R, std::set<u64>& P, std::set<u64>& X) override;
  void getMaxIndSetsBK2() override;
  u64 findMaxDegreeLst(std::set<u64> set) override;
  u64 findMaxDegreeMat(std::vector<u64> set) override;

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

  void expandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q) override;   // Procédure
  // récursive de recherche par arbre couvrant des
  // cliques

  void getAllMaxCliques(std::set<u64> vertices) override;   // Calcul effectif des cliques maximales


  std::set<u64> getListOfNeighboors(u64 i) override;
protected:
  std::unique_ptr<Graph> make(u64 n) override;
};