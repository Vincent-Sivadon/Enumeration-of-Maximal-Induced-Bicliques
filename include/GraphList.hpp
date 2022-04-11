#pragma once

#include "Graph.hpp"

/* ============================== POUR UNE LISTE D'ADJACENCE
 * ============================== */

class GraphList : public Graph {
public:
  /* =========== MEMBRES =========== */
  std::map<u64, std::set<u64>> adj;

  GraphList(u64 n) : Graph(n) {}

  /* ======== CONNECTIONS ENTRE SOMMETS ======== */
  void connect(u64 i, u64 j) override;
  bool areConnected(u64 i, u64 j) override;
  std::vector<int> verticesdegrees()
          const override;   // Permet de connaitre Le degré de chaque sommet dans le graphe
  void disconnect(u64 i,
                  u64 j) override;   // supprimer le lien entre deux sommets i et j

  /* =========== VISUALISATION =========== */
  void print() const override;

  static GraphList random(u64 N);

protected:
  std::unique_ptr<Graph> make(u64 n) override;
};