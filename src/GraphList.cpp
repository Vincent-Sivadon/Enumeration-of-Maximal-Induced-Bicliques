#include "GraphList.hpp"
#include <omp.h>

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

  for (u64 i = 0; i < orderedVertices.size(); i++) {
    auto nh = adj.extract(orderedVertices[i]);
    nh.key() = i;
    adj.insert(std::move(nh));
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
        break;
      }
    }

    return status;
  }
}

/*
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

void expandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q,
                      std::set<std::set<u64>> &stockCliques)
{
  if (SUBG.empty()) {
    if (isClique(Q, graph)) { stockCliques.push_back(Q); };
    std::cout << " clique, ";
  } else {
    int currentPivot = choosePivotElement(SUBG, CAND, graph);
    std::vector<int> gammaPivot = graph[currentPivot];
    std::vector<int> EXTu = diffOfSets(CAND, gammaPivot);
    while (not EXTu.empty()) {
      int q = EXTu[0];
      // int q = randchoice(EXTu);
      Q.push_back(q);
      std::cout << q << ", ";
      std::vector<int> gammaQ = graph[q];
      std::vector<int> SUBGq = intersectionOfSets(SUBG, gammaQ);
      std::vector<int> CANDq = intersectionOfSets(CAND, gammaQ);
      expandTomitaList(SUBGq, CANDq, Q, graph, stockCliques);
      std::vector<int> singleq = {q};
      // CAND.pop_back(q);
      // Q.pop_back(q);
      // Q = diffOfSets(Q,singleq);
      CAND = diffOfSets(CAND, singleq);
      std::cout << "back, ";
      Q = diffOfSets(Q, singleq);
      EXTu = diffOfSets(CAND, gammaPivot);
      // std::cout << "back, ";
    }
  }

}


void getAllMaxCliques(std::set<u64> vertices, std::set<std::set<u64>> &cliques) {
  std::cout << " Start of clique finding !"
            << "\n\n";
  std::vector<int> Q;
  expandTomitaList(vertices, vertices, Q, graph, cliques);
  std::cout << " End of clique finding !"
            << "\n";
}*/

std::set<std::set<u64>> GraphList::getBicliques_ALGO_2() {
  //
  Tree suffixTree;

  double getMaxIndSetsTIME = 0;
  std::vector<u64> orderedVertices;

  degenOrder(orderedVertices);

  //
  for (u64 i = 0; i < N; i++) {
    // Construct the subgraph G_i
    auto subgraph_i = genSubgraphGik(i);

    // Get all maximal independent sets of every subgraph Gik
    for (auto &it : subgraph_i) {
      std::set<std::set<u64>> IndSets;
      std::set<u64> tmpSet;
      double start = omp_get_wtime();
      std::set<std::set<u64>> maxIndSets = it->getMaxIndSets(IndSets, tmpSet);
      double end = omp_get_wtime();
      getMaxIndSetsTIME += end - start;

      // Rename the nodes
      std::set<std::set<u64>> globalMaxIndSets;   // sets with parent graph indices
      std::set<u64> tmp;
      for (const auto &maxIndSet : maxIndSets) {
        // Add the sets with parent graph indices
        tmp.clear();
        for (const auto &el : maxIndSet) tmp.insert(el + i);
        globalMaxIndSets.insert(tmp);
      }

      // Add maxIndSet
      for (const auto &maxIndSet : globalMaxIndSets) suffixTree.insert(maxIndSet);
    }
  }

  // On isole les branches maximale de l'arbre de suffix
  std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

  std::cout << "getMaxIndSets Time : " << getMaxIndSetsTIME << std::endl;

  return bicliques;
}