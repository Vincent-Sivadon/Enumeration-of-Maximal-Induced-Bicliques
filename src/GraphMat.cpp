#include "GraphMat.hpp"

// Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
void GraphMat::connect(u64 i, u64 j) {
  adj[i * N + j] = 1;
  adj[j * N + i] = 1;
}

// Indique si deux sommets sont reliés ou non
bool GraphMat::areConnected(u64 i, u64 j) {
  // Si adj[i][j] = 1 alors connectés sinon adj[i][j] = 0
  return adj[i * N + j];
}

// Affiche le contenu de la matrice d'adjacence
void GraphMat::print() const {
  // Pour chaque paire de sommet (i,j)
  for (u64 i = 0; i < N; i++) {
    for (u64 j = 0; j < N; j++) { std::cout << adj[i * N + j] << " "; }
    std::cout << "\n";
  }
}

std::unique_ptr<Graph> GraphMat::make(u64 n) { return std::make_unique<GraphMat>(n); }

GraphMat GraphMat::random(u64 N) {
  GraphMat res(N);
  res.randomize();

  return res;
}

// Permet de connaitre le degré de tous les sommets du graphe
std::vector<int> GraphMat::verticesdegrees() const {
  std::vector<int> vertDeg(N);
  int ctn = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (adj[i * N + j] == 1) ctn++;
  vertDeg.push_back(ctn);

  return vertDeg;
}

// Supprimé le lien entre deux sommets i et j
void GraphMat::disconnect(u64 i, u64 j) {
  adj[i * N + j] = 0;
  adj[j * N + i] = 0;
}