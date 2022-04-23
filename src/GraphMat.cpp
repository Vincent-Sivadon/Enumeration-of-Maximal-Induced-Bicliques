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


std::vector<u64> GraphMat::findDegrees() {
  std::vector<u64> vertDeg(N);

  for (int i = 0; i < N; i++) {
    u64 nbVoisins = 0;
    for (int j = 0; j < N; j++)
      if (adj[i * N + j] == 1) nbVoisins++;
    vertDeg[i] = nbVoisins;
  }

  return vertDeg;
}

//
void GraphMat::deleteVertex(u64 i) {
  // Search for all i neighboors
  for (int k = 0; k < N; k++) {
    if (adj[i * N + k] == 1) adj[i * N + k] = 0;
    if (adj[k * N + i] == 1) adj[k * N + i] = 0;
  }
}

//
void GraphMat::findMinDegree(u64 &vertexMinDeg, u64 &minDeg) {
  std::vector<u64> vertDeg = findDegrees();
  vertexMinDeg = 0;
  minDeg = 0;

  for (int i = 0; i < N; i++) {
    if (vertDeg[i] <= 0) continue;
    vertexMinDeg = i;
    break;
  }
  minDeg = vertDeg[vertexMinDeg];

  for (u64 i = 0; i < N; i++)
    if (vertDeg[i] < minDeg) {
      minDeg = vertDeg[i];
      vertexMinDeg = i;
    }
}

void GraphMat::degenOrder(std::vector<u64> &orderedVertices) {
  // Allocation
  orderedVertices.resize(N);
  std::vector<int> checkTab(N);
  for (int i = 0; i < N; i++) checkTab[i] = 0;
  int nbRestant = N;
  u64 tmp = 0;
  u64 vertexMinDeg, minDeg;

  for (int i = 0; i < N; i++) {
    if (nbRestant > 2) {
      findMinDegree(vertexMinDeg, minDeg);
      orderedVertices[i] = vertexMinDeg;
      nbRestant -= 1;
      checkTab[vertexMinDeg] = 1;
      deleteVertex(i);
    }

    else if (nbRestant == 2) {
      findMinDegree(vertexMinDeg, minDeg);
      orderedVertices[i] = vertexMinDeg;
      nbRestant -= 1;
      checkTab[vertexMinDeg] = 1;
      std::vector<int>::iterator it;
      it = std::find(checkTab.begin(), checkTab.end(), 0);
      auto val = it - checkTab.begin();
      if (it != checkTab.end()) {
        orderedVertices[i + 1] = val;
        break;
      }
    }
  }
}

void GraphMat::changeToComplementary() {
  for (int i = 0; i < N * N; i++) adj[i] == 0 ? adj[i] = 1 : adj[i] = 0;
}

//
bool GraphMat::isClique(std::set<u64>& edgeSets)
{
  int n = edgeSets.size();
  bool status = true;
  if (n < 3) return false;

  for (auto i : edgeSets) {
    u64 nbVoisins = 0;
    for (int j = 0; j < N; j++)
      if (adj[i * N + j] == 1) nbVoisins++;
    
    if(nbVoisins != n-1)
    {
      status = false;
      break;
    }
    }
  return status;
}