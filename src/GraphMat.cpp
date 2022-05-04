#include "GraphMat.hpp"
#include <omp.h>
#include "vector"

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

// GraphMat GraphMat::random(u64 N) {
//   GraphMat res(N);
//   res.randomize();

//   return res;
// }


// Supprimé le lien entre deux sommets i et j
void GraphMat::disconnect(u64 i, u64 j) {
  adj[i * N + j] = 0;
  adj[j * N + i] = 0;
}


// Permet de connaitre le degré de tous les sommets du graphe
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
    if ((adj[i * N + k] == 1)&& k !=i) adj[i * N + k] = 0;
    if ((adj[k * N + i] == 1)&& k!= i) adj[k * N + i] = 0;
  }
}


bool GraphMat::isNeighborhEmpty(u64 i)
{
  int cnt = 0;
  for(u64 j = 0; j < N; j++) 
  {
    if(adj[i*N +j ] == 1)
      cnt++;
  }
  return (cnt <= 0);
}

/* Fonction utilitaire Bron Kerbosch*/

//Nécessité de calculer le sommet de plus grand degré pour le choix du pivot

u64 GraphMat::findMaxDegreeMat(std::vector<u64> set) {
  std::vector<u64> vertDeg = findDegrees();
  u64 vertexMaxDeg = 0;
  u64 maxDeg = 0;

  for(const auto& i : set) {
    if (vertDeg[i] <= 0) continue;
    vertexMaxDeg = i;
    break;
  }
  maxDeg = vertDeg[vertexMaxDeg];

  for(const auto& i : set) {
    if ((vertDeg[i] > maxDeg) && !(isNeighborhEmpty(i))) {
      maxDeg = vertDeg[i];
      vertexMaxDeg = i;
    }
  }
  return vertexMaxDeg;
}

u64 GraphMat::findMaxDegreeLst(std::set<u64> set) {
  std::vector<u64> vertDeg = findDegrees();
  u64 vertexMaxDeg = 0;
  u64 maxDeg = 0;

  for(const auto& i : set) {
    if (vertDeg[i] <= 0) continue;
    vertexMaxDeg = i;
    break;
  }
  maxDeg = vertDeg[vertexMaxDeg];

  for(const auto& i : set) {
    if ((vertDeg[i] > maxDeg) && !(isNeighborhEmpty(i))) {
      maxDeg = vertDeg[i];
      vertexMaxDeg = i;
    }
  }
  return vertexMaxDeg;
}


/*
    - Seconde implémentation de Bron-Kerbosch
*/


/* ========================== BRON-KERBOSCH 2 ========================== */


void GraphMat::bronKerbosch2(std::set<u64>& R, std::set<u64>& P, std::set<u64>& X) {
  std::set<u64> r, p1, p2, x; 
  std::vector<u64> u1;

  if (P.empty() && X.empty()) cliques2.insert(R);

//Choisir un sommet pivot u dans P ⋃ X
for (const auto& i : X)
    u1.push_back(i); 
  const auto k = P.begin(); 
    u1.push_back(*k);

  u64 u2 = findMaxDegreeMat(u1);

  for (auto it = P.begin(); it != P.end(); ++it)
    if(!areConnected(u2, *it))
      {p1.insert(*it);}
      //std::cout<<*it<<std::endl;}

  for (auto v = p1.begin(); v != p1.end(); ++v) {

    r = u(R, *v);
    p2 = inter(P, *v);
    x = inter(X, *v);

    bronKerbosch2(r, p2, x);

    P.erase(*v);
    X.insert(*v);
  }

}

// Enumère tout les sets indépendants maximaux du graphe
void GraphMat::getMaxIndSetsBK2()
{
   std::set<u64> R;
   std::set<u64> X;
   std::set<u64> P;
   for (int i=0 ; i<N ; i++)
      P.insert(i);

   changeToComplementary();
   bronKerbosch2(R, P, X);
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
    if ((vertDeg[i] < minDeg) && !(isNeighborhEmpty(i))) {
      minDeg = vertDeg[i];
      vertexMinDeg = i;
    }
}

bool GraphMat::isGraphEmpty()
{
  auto degrees = findDegrees();
    return std::all_of(degrees.cbegin(), degrees.cend(), [](auto const &e)
                       { return e == 0; });
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
      deleteVertex(vertexMinDeg);
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

void GraphMat::changeToComplementary() {
  for (int i=0 ; i<N ; i++)
    for (int j=0 ; j<N ; j++)
      (adj[i*N + j] == 0 && i!=j) ? adj[i*N + j] = 1 : adj[i*N + j] = 0;
}

//
bool GraphMat::isClique(std::set<u64> &edgeSets) {
  int n = edgeSets.size();
  bool status = true;
  if (n < 3) return false;
for (auto i : edgeSets) {
    for (auto j : edgeSets) {
      if ((i != j) && !areConnected(i,j))
        {
          status = false;
          break;
        }
    }
  }
  return status;
}

std::set<std::set<u64>> GraphMat::getBicliques_ALGO_2() {
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

u64 GraphMat::ChooseMyPivot(std::set<u64> &CAND, std::set<u64> &SUB) {
  int pivot = -1;
  int maxSize = -1;

  for (const auto &u : SUB) {
    std::set<u64> gammaU;

    for (u64 i = 0; i < N; i++) {
      if (adj[u * N + i] == 1) gammaU.insert(i);
    }
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


void GraphMat::expandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q) {
  if (SUBG.empty()) {
    if (isClique(Q)) { cliques.insert(Q); };
    // std::cout << " clique, ";
  } else {
    u64 currentPivot = ChooseMyPivot(SUBG, CAND);

    std::set<u64> gammaPivot;

    for (u64 i = 0; i < N; i++) {
      if (adj[currentPivot * N + i] == 1) gammaPivot.insert(i);
    }
    std::set<u64> EXTu = diffOfSets(CAND, gammaPivot);
    while (not EXTu.empty()) {
      u64 q = *(EXTu.begin());
      // int q = randchoice(EXTu);
      Q.insert(q);
      // std::cout << q << ", ";
      std::set<u64> gammaQ;
      for (u64 i = 0; i < N; i++) {
        if (adj[currentPivot * N + i] == 1) gammaQ.insert(i);
      }
      std::set<u64> SUBGq = intersectionOfSets(SUBG, gammaQ);
      std::set<u64> CANDq = intersectionOfSets(CAND, gammaQ);
      expandTomita(SUBGq, CANDq, Q);
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


void GraphMat::getAllMaxCliques(std::set<u64> vertices) {
  std::set<u64> Q;
  expandTomita(vertices, vertices, Q);
}


std::set<u64> GraphMat::getListOfNeighboors(u64 i)
{
  std::set<u64> neighboors;
  for (int j=0 ; j<N ; j++)
    if (adj[i*N+j] == 1)
      neighboors.insert(j);
    
  return neighboors;
}