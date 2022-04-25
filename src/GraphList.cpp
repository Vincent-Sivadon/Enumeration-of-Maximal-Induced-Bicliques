#include "GraphList.hpp"

// Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
void GraphList::connect(u64 i, u64 j) {
  adj[i].insert(j);   // insère i dans la liste des voisins de j
  adj[j].insert(i);   // insère j dans la liste des voisins de i
}

// Indique si deux sommets sont reliés ou non
bool GraphList::areConnected(u64 i, u64 j) {
  // pour chaque sommet 'v' de la liste des voisins de i
  for (const auto &v : adj[i])
    if (v == j) return true;
  return false;
}

// Affiche le contenu de la liste d'adjacence
void GraphList::print() const {
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
std::unique_ptr<Graph> GraphList::make(u64 n) { return std::make_unique<GraphList>(n); }

GraphList GraphList::random(u64 N) {
  GraphList res(N);
  res.randomize();

  return res;
}

// Permet de connaitre le degré de tous les sommets du graphe
std::vector<int> GraphList::verticesdegrees() const {
  std::vector<int> vertDeg(N);

  for (auto &i : adj) vertDeg.push_back(i.second.size());
  return vertDeg;
}

// Supprimé le lien entre deux sommets i et j
void GraphList::disconnect(u64 i, u64 j) {
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

std::vector<u64> GraphList::findDegrees() {
  std::vector<u64> vertDeg(N);

  for (const auto &adji : adj) vertDeg[adji.first] = adji.second.size();

  return vertDeg;
}

//
void GraphList::deleteVertex(u64 i) {
  std::set<u64> voisins;
  voisins = adj[i];

  adj.erase(i);

  for (const auto &node : voisins) adj[node].erase(i);
}

//
void GraphList::findMinDegree(u64 &vertexMinDeg, u64 &minDeg) {
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

//
void GraphList::degenOrder(std::vector<u64> &orderedVertices) {
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
      auto it = std::find(checkTab.begin(), checkTab.end(), 0);
      auto val = it - checkTab.begin();
      if (it != checkTab.end()) {
        orderedVertices[i + 1] = val;
        break;
      }
    }
  }
}

void GraphList::changeToComplementary() {
  std::set<u64> newNeighboors;
  for (int i = 0; i < N; i++) {
    newNeighboors.clear();
    for (int j = 0; j < N; j++) {
      // If vertex j is not in neighboors of i, than insert in newNeighboors
      if (adj[i].find(j) == adj[i].end()) newNeighboors.insert(j);
    }
    adj[i] = newNeighboors;
  }
}


bool GraphList::isClique(std::set<u64> &edgeSets) {
  u64 n = edgeSets.size();
  bool status = true;
  if (n < 3) return false;

  for (auto i : edgeSets) {
    std::map<u64, std::set<u64>>::iterator it;
    for (it = adj.begin(); it != adj.end(); it++) {
      if ((it->first == i) && (it->second.size() != (n - 1))) {
        status = false;
         //  return status;
      }
    }


  }
return status;
}


u64 GraphList::ChooseMyPivot(std::set<u64> &CAND, std::set<u64> &SUB) {
  int pivot = -1;
  int maxSize = -1;

  for (const auto &u : SUB) {
    std::set<u64> gammaU = adj[u];
    std::set<u64> inter = intersectionOfSets(gammaU, CAND);
    u64 sizeOfInter = inter.size();

    if (sizeOfInter >= maxSize) {
      pivot = u;
      maxSize = sizeOfInter;
    }
  }

  return pivot;
}

//



 void GraphList::expandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q,
                  std::set<std::set<u64>> &stockCliques) {
  if (SUBG.empty()) {
     
    if (isClique(Q)) { stockCliques.insert(Q); };
     //std::cout << " clique, ";
  } else {
    u64 currentPivot = ChooseMyPivot(SUBG, CAND);
    std::set<u64> gammaPivot = adj[currentPivot];
    std::set<u64> EXTu = diffOfSets(CAND, gammaPivot);
    while (not EXTu.empty()) {
      u64 q = *(EXTu.begin());
      // int q = randchoice(EXTu);
      Q.insert(q);
      //std::cout << q << ", ";
      std::set<u64> gammaQ = adj[q];
      std::set<u64> SUBGq = intersectionOfSets(SUBG, gammaQ);
      std::set<u64> CANDq = intersectionOfSets(CAND, gammaQ);
      expandTomita(SUBGq, CANDq, Q,stockCliques);
      std::set<u64> singleq = {q};
      // CAND.pop_back(q);
      // Q.pop_back(q);
      // Q = diffOfSets(Q,singleq);
      CAND = diffOfSets(CAND, singleq);
      //std::cout << "back, ";
      Q = diffOfSets(Q, singleq);
      EXTu = diffOfSets(CAND, gammaPivot);
      // std::cout << "back, ";
    }
  }
}


void GraphList::getAllMaxCliques(std::set<u64> vertices, std::set<std::set<u64>> &cliques) {
  std::cout << " Start of clique finding !"
            << "\n\n";
  std::set<u64> Q;
  expandTomita(vertices, vertices, Q, cliques);
  std::cout << " End of clique finding !"
            << "\n";
}