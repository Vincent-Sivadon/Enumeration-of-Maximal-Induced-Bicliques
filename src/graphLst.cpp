#include "grapheLst.hpp"

// Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
void GraphLst::connect(u64 i, u64 j) {
  adj[i].insert(j);   // insère i dans la liste des voisins de j
  adj[j].insert(i);   // insère j dans la liste des voisins de i
}

// Indique si deux sommets sont reliés ou non
bool GraphLst::areConnected(u64 i, u64 j) {
  // pour chaque sommet 'v' de la liste des voisins de i
  for (const auto &v : adj[i])
    if (v == j) return true;
  return false;
}

// Affiche le contenu de la liste d'adjacence
void GraphLst::print() const {
  // Pour chaque sommet 'vertex' et sa liste de voisin 'vertexNeighboors'
  for (const auto &[vertex, vertexNeighboors] : adj) {
    //
    std::cout << "\n Neighboors of vertex " << vertex << " :\n";

    // affiche l'indice de chaque sommet de la liste de voisins
    for (const auto &i : vertexNeighboors) std::cout << " -> " << i;

    //
    std::cout << "\n";
  }
}

//
std::unique_ptr<Graph> GraphLst::make(u64 n) { return std::make_unique<GraphLst>(n); }

GraphLst GraphLst::random(u64 N) {
  GraphLst res(N);
  res.randomize();

  return res;
}

// Permet de connaitre le degré de tous les sommets du graphe
std::vector<int> GraphLst::verticesdegrees() const {
  std::vector<int> vertDeg(N);

  for (auto &i : adj) vertDeg.push_back(i.second.size());
  return vertDeg;
}

// Supprimé le lien entre deux sommets i et j
void GraphLst::deConnected(u64 i, u64 j) {
  /*// parcourir la liste des voisins du premier sommet à la recherche du second
  puis le supprimer dès qu'on l'aura trouver for (int k = 0; k < adj[i].size();
  k++)
  {
      if (adj[i][k] == j)
      {
          adj[i].erase(adj[i].begin + k);
          break;
      }
  }*/
}