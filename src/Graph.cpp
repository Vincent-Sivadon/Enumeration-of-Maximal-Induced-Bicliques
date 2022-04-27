/*
    - Contient l'implémentation de l'interface structure Graph
*/

#include "Graph.hpp"

#include <algorithm>
#include <mpi.h>
#include <omp.h>

/* =============================== SETS =============================== */

// Retourn un booléen indiquant si un set est propre par rapport au graphe
bool Graph::isProper(std::set<u64> set) {
  for (auto i = set.begin(); i != set.end(); i++)
    for (auto j = set.begin(); j != set.end(); j++)
      if (i != j)
        if (areConnected(*i, *j)) return true;
  return false;
}

// Indique si vertex est connecté au set dans le graphe
bool Graph::isConnectedToSet(u64 v, std::set<u64> set) {
  for (const auto &u : set) {
    if (areConnected(v, u)) return true;
  }
  return false;
}

// Enumère tout les set indépendants
void Graph::getIndSets(std::set<std::set<u64>> &IndSets, std::set<u64> &tmpSet, u64 i) {
  for (u64 j = i; j < N; j++) {
    // On ajoute j au tmpSet si il n'est connecté à aucun k de tmpSet
    if (isConnectedToSet(j, tmpSet)) continue;

    // Si on a passé le test, on insert j
    tmpSet.insert(j);

    // on refait la procédure à partir de j+1
    getIndSets(IndSets, tmpSet, j + 1);

    // Puisqu'on a construit le set indépendants qui partait de j, on le
    // supprime du tmpSet
    tmpSet.erase(j);
  }
  IndSets.insert(tmpSet);
}

// Enumère tout les sets indépendants maximaux du graphe
std::set<std::set<u64>> Graph::getMaxIndSets(std::set<std::set<u64>> &IndSets, std::set<u64> &tmpSet) {
  //
  IndSets.clear();
  tmpSet.clear();
  std::set<std::set<u64>> maxIndSets;

  // Get all independent sets
  getIndSets(IndSets, tmpSet, 0);

  // Taille du set maximal pour pouvoir isoler que les max ind sets
  u64 maxSize = 0;
  for (const auto &set : IndSets)
    if (set.size() > maxSize) maxSize = set.size();

  // On garde uniquement les sets de taille maximale
  for (const auto &set : IndSets)
    if (set.size() == maxSize) maxIndSets.insert(set);

  return maxIndSets;
}

/* ========================== BRON-KERBOSCH ========================== */

// L'algorithme de Bron Kerbosch utilise l'union et l'intersection
// d'ensembles, on commence donc par implémenter une fonction union et inter.

std::set<u64> Graph::u(std::set<u64> uni, u64 v) {
  uni.insert(v);
  return uni;
}

/*Pour la fonction intersection,
il faut obtenir le set et les voisions du second élément*/

std::set<u64> Graph::inter(std::set<u64> set, u64 v) {
  std::set<u64> intersection;

  for (auto k = set.begin(); k != set.end(); k++)
    if (areConnected(v, *k)) intersection.insert(v);
  return intersection;
}

std::set<std::set<u64>> cliques1;

std::set<std::set<u64>> Graph::bronKerbosch(std::set<u64> R, std::set<u64> P, std::set<u64> X) {
  std::set<u64> r, p, x;

  if (P.empty() && X.empty()) cliques1.insert(R);
  else {
    for (auto v : P) {
      r = u(R, v);
      p = inter(P, v);
      x = inter(X, v);
      bronKerbosch(r, p, x);
      P.erase(v);
      X.insert(v);
    }
  }

  return cliques1;
}

std::set<u64> Graph::prepareBron(std::set<u64> R, std::set<u64> P, std::set<u64> X) {
  for (auto i = 0; i < N; i++) P.insert(i);

  bronKerbosch(R, P, X);

  return P;
}

// Enumère tout les sets indépendants maximaux du graphe
std::set<std::set<u64>> Graph::getMaxIndSets2(std::set<std::set<u64>> cliques) {
  //
  std::map<u64, std::set<u64>> IndSets;
  std::set<std::set<u64>> maxIndSets;

  // Maximal set size
  u64 maxSize = 0;

  for (auto i : cliques)
    if (i.size() > maxSize) maxSize = i.size();

  for (auto i : cliques)
    if (i.size() == maxSize) maxIndSets.insert(i);

  return maxIndSets;
}

/*
    - Seconde implémentation de Bron-Kerbosch
*/


/* ========================== BRON-KERBOSCH 2 ========================== */

std::set<std::set<u64>> cliques2;

std::set<std::set<u64>> Graph::bronKerbosch2(std::set<u64> R, std::set<u64> P, std::set<u64> X) {
  std::set<u64> r, p1, p2, x, u1;

  if (P.empty() && X.empty()) cliques2.insert(R);

  for (auto k : P) { u1 = u(X, k); }

  for (auto i : u1) { p1 = inter(P, i); }

  for (auto v : p1) {
    r = u(R, v);
    p2 = inter(P, v);
    x = inter(X, v);
    bronKerbosch2(r, p2, x);
    P.erase(v);
    X.insert(v);
  }

  return cliques2;
}

/* ============================= UTILITAIRE ============================= */

// Donne la longueur du plus court chemin depuis src pour chaque sommet
std::vector<u64> Graph::shortestPaths(u64 src) {
  /* On crée un tableau dynamique pour stocker les distances et on et
  initialise toutes les distances à l'infini.
  Et on crée un ensemble pour dire si les sommets ont été visités */
  std::vector<u64> dist(N, INF);
  std::vector<bool> visited(N, false);

  // On intialise ça distance à 0
  dist[src] = 0;

  // On fera au maximum N iterations
  for (u64 j = 0; j < N; j++) {
    // On calcul l'index du noeud pour lequel la distance est minimal
    // On le supprime donc de l'ensemble
    u64 u = minDist(dist, visited);
    visited[u] = true;

    // On vérifie que u ne dépasse pas la distance souhaitée
    if (dist[u] >= 2) break;

    // On boucle sur tous les voisins contenues dans adj
    for (u64 v = 0; v < N; v++) {
      // si adj[u][v] = 0 alors ils ne sont pas voisins
      if (!areConnected(u, v)) continue;

      // On met à jour la plus courte distance si besoin
      if (dist[v] > dist[u] + 1 && !visited[v]) dist[v] = dist[u] + 1;
    }
  }

  return dist;
}

// From the 2 sets of an original biclique, indicates if by adding i, biclique is still viable
bool Graph::isViableBiclique(std::set<u64> &X, std::set<u64> &Y, u64 i) {
  // If one of the sets is empty, it is a degenerated cases
  if (X.size() == 0 || Y.size() == 0) return false;

  // Indicates if a biclique is viable
  bool viable = true;

  // If node is connected to an element from X
  // check if he's connected to all elements from X, and none elements from Y
  if (areConnected(i, *X.begin())) {
    // Check if connected to all elements of X
    for (const auto &node : X)
      if (!areConnected(i, node))   // if not, than this is not a viable biclique
        viable = false;

    // if the biclique is still viable, check if it's not connected to any elements of Y
    if (viable)
      for (const auto &node : Y)
        if (areConnected(i, node))   // if it is, than this i not a viable biclique
          viable = false;
  }
  // do it the opposite way if not connected to X
  else if (areConnected(i, *Y.begin())) {
    // Check if connected to all elements of Y
    for (const auto &node : Y)
      if (!areConnected(i, node))   // if not, than this is not a viable biclique
        viable = false;

    // if the biclique is still viable, check if it's not connected to any elements of X
    if (viable)
      for (const auto &node : X)
        if (areConnected(i, node))   // if it is, than this i not a viable biclique
          viable = false;
  }
  // else if not connected to any element of X or Y, not viable
  else
    viable = false;

  // Return
  if (viable) return true;
  else
    return false;
}

bool Graph::isBicliqueMaximale(const std::set<u64> &biclique) {
  if (biclique.size() == 1) return false;

  std::set<u64> X, Y;

  // Constructs sets X et Y
  // ----------------------
  X.insert(*biclique.begin());   // insert first node
  for (const auto &node : biclique) {
    // If node is connected to an element from X : insert node in Y
    // else : insert node in X
    if (areConnected(node, *X.begin())) Y.insert(node);
    else
      X.insert(node);
  }

  /* For every node in 1:n
   * add this node to biclique
   * check if it's still a biclique */
  for (u64 i = 0; i < N; i++) {
    if (X.find(i) != X.end() || Y.find(i) != Y.end()) continue;
    if (isViableBiclique(X, Y, i)) return false;
  }

  // If all the biclique passed all tests, it is maximale
  return true;
}

/* ======================== PROCEDURE DE L'ARTICLE ======================== */

// Génère les sous-graphes d'après le papier (sigma contiendra l'ordre des
// sommets)
std::unique_ptr<Graph> Graph::genSubgraph(u64 i) {
  // Obtenir les distances au sommet i
  std::vector<u64> dist = shortestPaths(i);

  //
  auto subgraph = make(N - i);

  // Run through all pairs of nodes in the parent graph
  for (u64 x = i; x < N; x++)
    for (u64 y = x + 1; y < N; y++) {
      bool are_connected = areConnected(x, y);

      // Conditions  de construction des arretes
      bool x_dist1 = dist[x] == 1;
      bool y_dist1 = dist[y] == 1;
      bool x_dist2 = dist[x] == 2;
      bool y_dist2 = dist[y] == 2;

      // Conditions  de construction des arretes
      bool cond1 = x_dist1 && y_dist1 && are_connected;
      bool cond2 = x_dist2 && y_dist2 && are_connected;
      bool cond3 = x_dist1 && y_dist2 && !are_connected;
      bool cond4 = x_dist2 && y_dist1 && !are_connected;

      // Ajouter une arrete si l'une des conditions est vérifiée
      if (cond1 || cond2 || cond3 || cond4)
        // Add node x and y with new indices to the pairs of the subgraph
        subgraph->connect(x - i, y - i);
    }

  return subgraph;
}

// fonction utilitaire pour stocker les sommets à distance un et deux
std::vector<std::vector<u64>> Graph::tables_of_neighbors(u64 i) {
  std::vector<u64> dist = shortestPaths(i);
  std::vector<u64> neighbors_dist1;

  std::vector<std::vector<u64>> tables;

  tables.push_back(dist);


  for (u64 i = 0; i < dist.size(); i++) {
    if (dist[i] == 1) { neighbors_dist1.push_back(i); }
  }

  tables.push_back(neighbors_dist1);

  return tables;
}

// Fonction qui génére tous les sous graphes Gik pour un graphe Gi donné

std::vector<std::unique_ptr<Graph>> Graph::genSubgraphGik(u64 i) {
  std::vector<std::vector<u64>> tables = tables_of_neighbors(i);
  std::vector<u64> dist1;
  std::vector<u64> dist = tables[0];

  // Initialisation du tableau contenant l'ensemble des sous graphes Gik
  std::vector<std::unique_ptr<Graph>> all_subgraph_Gik;

  for (auto const &it : tables[1]) {
    // Boucles qui balayent sur toutes les paires de noeuds dans le graphe initial

    dist1 = shortestPaths(it);
    auto subgraph = make(N);

    for (u64 x = i; x < N; x++)
      for (u64 y = x + 1; y < N; y++) {
        bool are_connected = areConnected(x, y);

        // Conditions  de construction des arretes

        bool x_dist1 = dist[x] == 1;
        bool y_dist1 = dist[y] == 1;
        bool x_dist2 = dist[x] == 2;
        bool y_dist2 = dist[y] == 2;
        bool x_dist1_it = dist1[x] == 1;
        bool y_dist1_it = dist1[y] == 1;

        bool cond1 = x_dist1 && y_dist1 && are_connected;

        // Conditon de verification pour les arretes

        bool cond2 = x_dist2 && y_dist2 && x_dist1_it && y_dist1_it && are_connected;

        bool cond3 = x_dist1 && y_dist2 && y_dist1_it && !are_connected;
        bool cond4 = y_dist1 && x_dist2 && x_dist1_it && !are_connected;

        if (cond1 || cond2 || cond3 || cond4) subgraph->connect(x, y);
      }

    // On ajoute le sous graph obtenu aux tableaux contenant l'ensemble des
    // sous graph Gik
    all_subgraph_Gik.push_back(std::move(subgraph));
  }
  return all_subgraph_Gik;
}

// Enumère tout les bicliques maximales du graphe
std::set<std::set<u64>> Graph::getBicliques() {
  //
  Tree suffixTree;

  double getMaxIndSetsTIME = 0;

  //
  for (u64 i = 0; i < N; i++) {
    // Construct the subgraph G_i
    auto subgraph_i = genSubgraph(i);

    // Get all maximal independent sets of G_i
    std::set<std::set<u64>> IndSets;
    std::set<u64> tmpSet;
    double start = omp_get_wtime();
    std::set<std::set<u64>> maxIndSets = subgraph_i->getMaxIndSets(IndSets, tmpSet);
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
    for (const auto &maxIndSet : globalMaxIndSets)
      if (isProper(maxIndSet)) suffixTree.insert(maxIndSet);
  }

  // On isole les branches maximale de l'arbre de suffix
  std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

  // std::cout << "getMaxIndSets Time : " << getMaxIndSetsTIME << std::endl;

  return bicliques;
}

std::set<std::set<u64>> Graph::getBicliquesParallel() {
  Tree suffixTree;

  int nproc, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  u64 Q = N / nproc;
  u64 R = N % nproc;
  u64 nb_iter = (rank < R ? Q + 1 : Q);
  u64 i_first = (rank < R ? rank * (Q + 1) : (rank - R) * Q + R * (Q + 1));

  // For every nodes
#pragma omp parallel for
  for (u64 i = i_first; i < i_first + nb_iter; i++) {
    // Construct the subgraph G_i
    auto subgraph_i = genSubgraph(i);

    std::set<std::set<u64>> IndSets;
    std::set<u64> tmpSet;
    // Get all maximal independent sets of G_i
    std::set<std::set<u64>> maxIndSets = subgraph_i->getMaxIndSets(IndSets, tmpSet);

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
    for (const auto &maxIndSet : globalMaxIndSets)
      if (isProper(maxIndSet))
#pragma omp critical
        suffixTree.insert(maxIndSet);
  }

  // On isole les branches maximale de l'arbre de suffix
  std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

  std::string filename("bicliques" + std::to_string(rank));
  FILE *fp = fopen(filename.c_str(), "w");
  for (const auto &biclique : bicliques) {
    for (const auto &node : biclique) fprintf(fp, "%llu ", node);
    fprintf(fp, "\n");
  }
  fclose(fp);

  MPI_Finalize();

  return bicliques;
}

/* =========================== GENERATION DE GRAPHE ===========================
 */

// Génère un graphe pour lequel chaque sommet a 50% de chance d'être connecté à
// un autre sommet

void Graph::randomize() {
  // Déclaration d'un nouveau graphe

  // On ajoute une arrête entre i et j avec une probabilité de 50%
  for (u64 i = 0; i < N; i++)
    for (u64 j = 0; j < N; j++) {
      // Nombre aléatoire entre 0 et 1
      double r = (double) rand() / (double) RAND_MAX;

      // Connecte i et j si r<0.5
      if (r < 0.5) connect(i, j);
    }
}

/* =========================== FONCTION UTILITAIRE ===========================
 */

// Recherche du sommet avec la distance minimale
u64 minDist(std::vector<u64> &dist, std::vector<bool> &visited) {
  // On initialisa la distance minimal à l'infini et l'index du noeud pour
  // lequel la distance est minimal
  u64 min = INF, min_index = 0;

  for (u64 v = 0; v < dist.size(); v++)
    if (!visited[v] && dist[v] <= min) min = dist[v], min_index = v;

  return min_index;
}

void printSets(std::set<std::set<u64>> sets) {
  for (auto &set : sets) {
    for (auto &i : set) { std::cout << i << " "; }
    std::cout << "\n";
  }
}

// calcul la différence ensembliste A\B
std::set<u64> Graph::diffOfSets(std::set<u64> &A, std::set<u64> &B) {
  std::set<u64>::iterator it;
  std::set<u64> output;
  for (auto i : A) {
    it = std::find(B.begin(), B.end(), i);
    if (it == B.end()) output.insert(i);
  }
  return output;
}

// calcul de l'intersection de deux ensembles
std::set<u64> Graph::intersectionOfSets(std::set<u64> &A, std::set<u64> &B) {
  std::set<u64>::iterator it;
  std::set<u64> output;
  for (auto i : B) {
    it = std::find(A.begin(), A.end(), i);
    if (it != A.end()) output.insert(i);
  }
  return output;
}

// calcul de la réunion de deux ensembles
std::set<u64> Graph::unionOfSets(std::set<u64> &A, std::set<u64> &B) {
  std::set<u64>::iterator it;
  std::set<u64> output = A;

  for (auto i : B) {
    it = std::find(A.begin(), A.end(), i);
    if (it == A.end()) A.insert(i);
  }
  return output;
}

// Opère un choix aléatoire d'élément du set v
u64 Graph::randchoice(std::set<u64> v) {
  std::random_device r_device;
  std::mt19937 engine{r_device()};
  std::uniform_int_distribution<u64> dist(0, v.size() - 1);

  std::set<u64>::iterator it;
  it = std::find(v.begin(), v.end(), dist(engine));
  u64 rand_elemnent = *it;
  return rand_elemnent;
}