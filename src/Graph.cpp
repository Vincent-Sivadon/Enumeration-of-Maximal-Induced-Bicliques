/*
    - Contient l'implémentation de l'interface structure Graph
*/

#include "Graph.hpp"

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
std::set<std::set<u64>> Graph::getMaxIndSets(std::set<std::set<u64>> &IndSets,
                                             std::set<u64> &tmpSet) {
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

// Fonction qui génére tous les sous graphes Gik pour un graphe Gi donné

std::vector<std::unique_ptr<Graph>> Graph::genSubgraphGik(u64 i) {
  std::vector<u64> dist = shortestPaths(i);

  // Initialisation du tableau contenant l'ensemble des sous graphes Gik
  std::vector<std::unique_ptr<Graph>> all_subgraph_Gik;

  // Boucles qui balayent sur toutes les paires de noeuds dans le graphe initial

  for (u64 x = i; x < N; x++)
    for (u64 y = x + 1; y < N; y++) {
      auto subgraph = make(0);

      bool are_connected = areConnected(x, y);

      // Conditions  de construction des arretes

      bool x_dist1 = dist[x] == 1;
      bool y_dist1 = dist[y] == 1;
      bool x_dist2 = dist[x] == 2;
      bool y_dist2 = dist[y] == 2;

      bool cond1 = x_dist1 && y_dist1 && are_connected;

      // Si x est à distance un de i, on peut créer un sous graph Gik à partir
      // de x
      if (x_dist1) {
        // On détermine l'ensemble des sommets à distance un de x
        std::vector<u64> dist1 = shortestPaths(x);

        // On boucle sur l'ensemble des sommets à distance un de x
        for (auto const &it : dist1) {
          // on vérifie les sommets à distance un de x
          bool u_dist1 = dist1[it] == 1;

          // Les conditions de contructions des arrêtes
          bool cond2 = x_dist2 && u_dist1 && y_dist2 && are_connected;

          bool cond3 = x_dist1 && u_dist1 && y_dist2 && !are_connected;

          if (cond1 || cond2 || cond3) subgraph->connect(x, y);
        }

        // On ajoute le sous graph obtenu aux tableaux contenant l'ensemble des
        // sous graph Gik

        all_subgraph_Gik.push_back(std::move(subgraph));
      }

      // On effectue les mêmes instructions qu'avec le premier if mais cette
      // fois ci on vérifie si y appartient à l'ensemble à distance 1 de i

      else if (y_dist1) {
        std::vector<u64> dist2 = shortestPaths(y);

        // Conditon de verification pour les arretes

        for (auto const &it : dist2) {
          bool u_dist1 = dist2[it] == 1;

          bool cond2 = x_dist2 && u_dist1 && y_dist2 && are_connected;

          bool cond3 = x_dist1 && u_dist1 && y_dist2 && !are_connected;

          if (cond1 || cond2 || cond3)
            // Add node x and y with new indices to the pairs of the subgraph
            subgraph->connect(x, y);
        }

        all_subgraph_Gik.push_back(std::move(subgraph));
      }
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

  std::cout << "getMaxIndSets Time : " << getMaxIndSetsTIME << std::endl;

  return bicliques;
}

std::set<std::set<u64>> Graph::getBicliquesParallel() {
  // Will store maximal induces bicliques
  std::set<std::set<u64>> bicliques;

  // For every nodes
#pragma omp parallel for
  for (u64 i = 0; i < N; i++) {
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

    for (const auto &biclique : globalMaxIndSets)
      if (isBicliqueMaximale(biclique))
#pragma omp critical
      {
        bicliques.insert(biclique);
      }
  }

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
std::set<u64> diffOfSets(std::set<u64> &A, std::set<u64> &B)
{
  std::set<u64>::iterator it;
  std::set<u64> output;
  for (auto i : A) {
    it = std::find(B.begin(), B.end(), i);
    if (it == B.end()) output.insert(i);
  }
  return output;
}

// calcul de l'intersection de deux ensembles
std::set<u64> intersectionOfSets(std::set<u64> &A, std::set<u64> &B)
{
  std::set<u64>::iterator it;
  std::set<u64> output;
  for (auto i : B) {
    it = std::find(A.begin(), A.end(), i);
    if (it != A.end()) output.insert(i);
  }
  return output;
}

// calcul de la réunion de deux ensembles
std::set<u64> unionOfSets(std::set<u64> &A, std::set<u64> &B)
{
  std::set<u64>::iterator it;
  std::set<u64> output = A;

  for (auto i : B) {
    it = std::find(A.begin(), A.end(), i);
    if (it == A.end()) A.insert(i);
  }
  return output;
} 

// Opère un choix aléatoire d'élément du set v
u64 randchoice(std::set<u64> v) 
{
   std::random_device r_device;
  std::mt19937 engine{r_device()};
  std::uniform_int_distribution<u64> dist(0, v.size() - 1);

  std::set<u64>::iterator it;
  it = std::find(v.begin(), v.end(), dist(engine));
  u64 rand_elemnent = *it;
  return rand_elemnent;
}