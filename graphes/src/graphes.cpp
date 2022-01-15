#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <utility>
# define INF 0x3f3f3f3f

#include "visualisation.hpp"
#include "graphes.hpp"

namespace GL {


/* ===================== CONNECTIONS ENTRE SOMMETS ===================== */

// Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
void Graph::connect(u64 i, u64 j) {
    adj[i].insert(j);   // insère i dans la liste des voisins de j
    adj[j].insert(i);   // insère j dans la liste des voisins de i
}

// Retourne un booléen indiquant si les sommets i et j sont connectés
bool Graph::areConnected(u64 i, u64 j) {
    // pour chaque sommet 'vertex' de la liste des voisins de i
    for(const auto& vertex : adj[i])
        if (vertex == j) return true;
    return false;
}




/* =========================== VISUALISATION =========================== */

// Affiche le graphe dans le terminal (à des fins de debug)
void Graph::print() {
    // Pour chaque sommet 'vertex' et sa liste de voisin 'vertexNeighboors'
    for(const auto& [vertex, vertexNeighboors] : adj)
    {
        //
        std::cout << "\n Neighboors of vertex " << vertex << " :\n";

        // affiche l'indice de chaque sommet de la liste de voisins
        for(const auto& i : vertexNeighboors)
            std::cout << " -> " << i;

        //
        std::cout << "\n";
            
    }
}

// dessine le graphe à l'écran
void Graph::draw() {
    // Appel à l'implémentation de "visualisation.cpp"
    drawGraph(*this);
}




/* =============================== SETS =============================== */

// Retourn un booléen indiquant si un set est propre par rapport au graphe
bool Graph::isProper(std::set<u64> set)
{
    for (auto i = set.begin(); i!= set.end();i++)
        for(auto j = set.begin(); j!=set.end();j++)
            if( i!=j)                
                if ( areConnected(*i,*j)) 
                    return true;
    return false;
}

// Indique si vertex est connecté au set
bool Graph::isConnectedToSet(u64 v, std::set<u64> set)
{
    for (auto u : set){
        if (areConnected(v, u)) return true;
    }
    return false;
}

// Enumère tout les sets indépendants maximaux du graphe
std::set<std::set<u64>> Graph::getMaxIndSets() {
    // Number of vertices
    u64 N = adj.size();

    //
    std::map<u64, std::set<u64>> IndSets;
    std::set<std::set<u64>> maxIndSets;

    // Maximal set size
    u64 maxSize = 0;

    // Get maximal independent sets from the starting node i
    for(const auto& [i, iNeighboors] : adj)
    {
        IndSets.insert({i, {i}});
        for(const auto& [j, jNeighboors] : adj)
        {
            if(i==j) continue;
            if( !isConnectedToSet(j, IndSets[i]) )
                IndSets[i].insert(j);
        }
        // update the max ind set size
        if(IndSets[i].size() > maxSize ) maxSize = IndSets[i].size();
    }

    // keep only the real maximal sets
    for(const auto& [v, IndSet] : IndSets)
        if (IndSet.size() == maxSize) maxIndSets.insert(IndSet);

    return maxIndSets;
}



/* ============================= UTILITAIRE ============================= */

// Recherche du sommet avec la distance minimale
u64 minDist(std::vector<u64>& dist, std::vector<bool>& visited) {
    // On initialisa la distance minimal à l'infini et l'index du noeud pour lequel la distance est minimal
    u64 min = INF, min_index=0;

    for(u64 v=0 ; v<dist.size() ; v++)
        if (!visited[v] && dist[v]<=min)
            min = dist[v], min_index = v;

    return min_index;
}

// Donne la longueur du plus court chemin depuis src pour chaque sommet
std::vector<u64> Graph::shortestPaths(u64 src) {    
    /* On crée un tableau dynamique pour stocker les distances et on et 
    initialise toutes les distances à l'infini.
    Et on crée un ensemble pour dire si les sommets ont été visités */
    u64 N = adj.size();
    std::vector<u64> dist(N, INF);
    std::vector<bool> visited(N, false);

    // On intialise ça distance à 0
    dist[src] = 0;

    // On fera au maximum N iterations
    for(u64 j=0 ; j<N ; j++)
    {
        // On calcul l'index du noeud pour lequel la distance est minimal 
        // On le supprime donc de l'ensemble
        u64 u = minDist(dist, visited);
        visited[u] = true;

        // On vérifie que u ne dépasse pas la distance souhaitée
        if (dist[u] >= 2) break;

        // On boucle sur tous les voisins contenues dans adj
        for(auto& v : adj[u])
        {

            // On met à jour la plus courte distance si besoin
            if (dist[v] > dist[u] + 1 && !visited[v])
                dist[v] = dist[u] + 1;
        }
    }

    return dist;
}





/* ======================== PROCEDURE DE L'ARTICLE ======================== */

// Génère les sous-graphes d'après le papier
Graph Graph::genSubgraph(u64 i) {
    // Get number of vertices
    u64 N = adj.size();

    // Obtenir les distances au sommet i
    std::vector<u64> dist = shortestPaths(i);

    //
    Graph subgraph;

    for(const auto& [x, xNeighboors] : adj)
        for(const auto& [y, yNeighboors] : adj)
        {
            if(x==y) continue;

            bool are_connected = areConnected(x, y);

            // Conditions  de construction des arretes
            bool x_dist1 = ( dist[x]==1 ? true : false );
            bool y_dist1 = ( dist[y]==1 ? true : false );
            bool x_dist2 = ( dist[x]==2 ? true : false );
            bool y_dist2 = ( dist[y]==2 ? true : false ); 

            // Conditions  de construction des arretes
            bool cond1 = x_dist1 && y_dist1 && are_connected ;
            bool cond2 = x_dist2 && y_dist2 && are_connected ;
            bool cond3 = x_dist1 && y_dist2 && !are_connected ;
            bool cond4 = x_dist2 && y_dist1 && !are_connected ;

            // Ajouter une arrete si l'une des conditions est vérifiée
            if ( cond1 || cond2 || cond3 || cond4 ) {
                subgraph.connect(x, y);
            }
        }

    return subgraph;
}

// Utility function
void insertProperSuffixes(std::set<u64> const& maxIndSet, std::set<std::set<u64>>& bicliques) {
    std::set<u64> properSuffixes;
    for(auto& el : maxIndSet) {
        properSuffixes.insert(el);
        bicliques.insert(properSuffixes);
    }
}

// Enumère tout les bicliques maximales du graphe
std::set<std::set<u64>> Graph::getBicliques() {
    // Number of vertices
    u64 N = adj.size();

    // Store bicliques
    std::set<std::set<u64>> bicliques;
    
    //
    for (const auto& [i, iNeighboors] : adj)
    {
        // Construct the subgraph G_i
        Graph subgraph_i = genSubgraph(i);

        // Get all maximal independent sets of G_i
        std::set<std::set<u64>> maxIndSets = subgraph_i.getMaxIndSets();

        for(const auto& maxIndSet : maxIndSets)
        {
            if (isProper(maxIndSet)) 
                // Search if maxIndSet is already in bicliques
                if (bicliques.find(maxIndSet) == bicliques.end()) 
                    insertProperSuffixes(maxIndSet, bicliques);
        }
    }

    return bicliques;
}




/* =========================== GENERATION DE GRAPHE =========================== */

// Génère un graphe pour lequel chaque sommet a 50% de chance d'être connecté à un autre sommet
Graph genRandGraph(u64 N) {
    // Déclaration d'un nouveau graphe
    Graph graph;

    // On ajoute une arrête entre i et j avec une probabilité de 50%
    for(u64 i=0 ; i<N ; i++)
        for(u64 j=0 ; j<N ; j++) {
            // Nombre aléatoire entre 0 et 1
            double r = (double) rand() / (double) RAND_MAX;

            // Connecte i et j si r<0.5
            if (r < 0.5) graph.connect(i, j);
        }
    
    return graph;
}




/* =========================== GRAPHES SIMPLES =========================== */

// Génère un graphe qui représente une molecule d'eau (à des fins de tests majoritairement)
Graph H2O() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    return graph;
}

// Génère un graphe qui représente une molecule de méthane (à des fins de tests majoritairement)
Graph Methane() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(0, 4);

    return graph;
}

// Génère un graphe qui représente une molecule en forme d'hexagone (à des fins de tests majoritairement)
Graph Hexagone() {
    Graph graph;

    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 4);
    graph.connect(4, 5);
    graph.connect(5, 0);
    
    return graph;
}


} // end namespace GL