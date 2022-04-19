#pragma once

#include "Graph.hpp"

class GraphMat : public Graph {
private:
  /* ============== MEMBRES ============== */
  std::vector<u64> adj;

public:
  GraphMat(u64 n) : Graph(n) { adj.resize(N * N); }

  /* ======== CONNECTIONS ENTRE SOMMETS ======== */
  void connect(u64 i, u64 j) override;

  bool areConnected(u64 i, u64 j) override;

  std::vector<int> verticesdegrees()
          const override;   // Permet de connaitre Le degré de chaque sommet dans le graphe

  void disconnect(u64 i,
                  u64 j) override;   // supprimer le lien entre deux sommets i et j

  /* =========== VISUALISATION =========== */
  void print() const override;

  static GraphMat random(u64 N);
  std::vector<u64> findDegrees() override;
  void deleteVertex(u64 i) override;
  void findMinDegree(u64 &vertexMinDeg, u64 &minDeg) override;
  void degenOrder(std::vector<u64> &orderedVertices) override;

protected:
  std::unique_ptr<Graph> make(u64 n) override;
};