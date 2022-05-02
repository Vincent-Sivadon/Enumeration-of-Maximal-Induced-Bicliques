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

  for (u64 i = 0; i < N; i++) {
    if ((vertDeg[i] < minDeg) && !(adj[i].empty())) {
      minDeg = vertDeg[i];
      vertexMinDeg = i;
    }
  }
}

bool GraphList::isGraphEmpty() {
  auto degrees = findDegrees();
  return std::all_of(degrees.cbegin(), degrees.cend(), [](auto const &e) { return e == 0; });
}

// Supprimé le lien entre deux sommets i et j
void GraphList::disconnect(u64 a, u64 b) {
  std::set<u64>::iterator it1;
  std::set<u64>::iterator it2;

  it1 = std::find(adj[a].begin(), adj[a].end(), b);

  if (it1 != adj[a].end()) adj[a].erase(it1);

  it2 = std::find(adj[b].begin(), adj[b].cend(), a);

  if (it2 != adj[b].cend()) adj[b].erase(it2);
}

//
void GraphList::degenOrder(std::vector<u64> &orderedVertices) {
  // Allocation
  orderedVertices.resize(N);
  std::vector<int> checkTab(N);
  for (u64 i = 0; i < N; i++) checkTab[i] = 0;
  int nbRestant = N;
  u64 tmp = 0;
  u64 vertexMinDeg, minDeg;


  for (u64 i = 0; i < N; i++)
  {
    if (nbRestant > 2) {
      findMinDegree(vertexMinDeg, minDeg);
      orderedVertices[i]= vertexMinDeg;
      //orderedVertices.push_back(vertexMinDeg);
      nbRestant -= 1;
      checkTab[vertexMinDeg] = 1;
      deleteVertex(vertexMinDeg);
      // for (auto u : adj[vertexMinDeg]) { disconnect(vertexMinDeg, u); }
    }

    else if (nbRestant == 2) {
      findMinDegree(vertexMinDeg, minDeg);
      orderedVertices[i] = vertexMinDeg;
      // orderedVertices.push_back(vertexMinDeg);
      nbRestant -= 1;
      checkTab[vertexMinDeg] = 1;
      auto it = std::find(checkTab.begin(), checkTab.end(), 0);
      auto val = it - checkTab.begin();
      if (it != checkTab.end()) {
        orderedVertices[i + 1] = val;
        // orderedVertices.push_back(val);
        break;
      }
    }
  }

  // for (u64 i = 0; i < orderedVertices.size(); i++) {
  //   auto nh = adj.extract(orderedVertices[i]);
  //   nh.key() = i;
  //   adj.insert(std::move(nh));
  // }
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

    return status;
  }
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


void GraphList::expandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q, std::set<std::set<u64>> &stockCliques) {
  if (SUBG.empty()) {
    if (isClique(Q)) { stockCliques.insert(Q); };
    // std::cout << " clique, ";
  } else {
    u64 currentPivot = ChooseMyPivot(SUBG, CAND);
    std::set<u64> gammaPivot = adj[currentPivot];
    std::set<u64> EXTu = diffOfSets(CAND, gammaPivot);
    while (not EXTu.empty()) {
      u64 q = *(EXTu.begin());
      // int q = randchoice(EXTu);
      Q.insert(q);
      // std::cout << q << ", ";
      std::set<u64> gammaQ = adj[q];
      std::set<u64> SUBGq = intersectionOfSets(SUBG, gammaQ);
      std::set<u64> CANDq = intersectionOfSets(CAND, gammaQ);
      expandTomita(SUBGq, CANDq, Q, stockCliques);
      std::set<u64> singleq = {q};
      // CAND.pop_back(q);
      // Q.pop_back(q);
      // Q = diffOfSets(Q,singleq);
      CAND = diffOfSets(CAND, singleq);
      // std::cout << "back, ";
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


std::set<u64> GraphList::getListOfNeighboors(u64 i)
{
  return adj[i];
}
