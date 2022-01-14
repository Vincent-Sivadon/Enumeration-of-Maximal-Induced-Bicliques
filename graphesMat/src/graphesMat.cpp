#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <utility>
# define INF 0x3f3f3f3f

#include "visualisationMat.hpp"
#include "graphesMat.hpp"

namespace GM {

    
// Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
void Graph::connect(u64 i, u64 j) {
    adj[i*N + j] = 1;
    adj[j*N + i] = 1;
}

// Affiche le graphe dans le terminal (à des fins de debug)
void Graph::print() {

    // Pour chaque paire de sommet (i,j)
    for(u64 i=0 ; i<N ; i++)
    {
        for(u64 j=0 ; j<N ; j++)
        {
            std::cout << adj[i*N + j] << " ";
        }
        std::cout << "\n";
    }
}

// Retourne un booléen indiquant si les sommets i et j sont connectés
bool Graph::areConnected(u64 i, u64 j) {
    // Si adj[i][j] = 1 alors connectés sinon adj[i][j] = 0
    return adj[i*N + j];
}

// dessine le graphe à l'écran
void Graph::draw() {
    // Appel à l'implémentation de "visualisation.cpp"
    drawGraph(*this);
}

// Génère un graphe pour lequel chaque sommet a 50% de chance d'être connecté à un autre sommet
Graph genRandGraph(u64 N) {
    // Déclaration d'un nouveau graphe
    Graph graph(N);

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
        for(u64 v=0 ; v<N ; v++)
        {
            // si adj[u][v] = 0 alors ils ne sont pas voisins
            if(adj[u*N + v]==0) continue;

            // On met à jour la plus courte distance si besoin
            if (dist[v] > dist[u] + 1 && !visited[v])
                dist[v] = dist[u] + 1;
        }
    }

    return dist;
}

// Génère les sous-graphes d'après le papier
Graph Graph::genSubgraph(u64 i) {

    // Obtenir les distances au sommet i
    std::vector<u64> dist = shortestPaths(i);

    //
    Graph subgraph(N);

    //
    for(u64 x=0 ; x<N ; x++)
        for(u64 y=x+1 ; y<N ; y++)
        {
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


// Indique si vertex est connecté au set dans le graphe
bool Graph::isNotConnectedToSet(u64 v, std::set<u64> set)
{
    for (auto u : set){
        if (areConnected(v, u)) return false;
    }
    return true;
}

// Enumère tout les sets indépendants maximaux du graphe
std::set<std::set<u64>> Graph::getMaxIndSets() {

    //
    std::map<u64, std::set<u64>> IndSets;
    std::set<std::set<u64>> maxIndSets;

    // Maximal set size
    u64 maxSize = 0;

    // Get maximal independent sets from the starting node i
    for(u64 i=0 ; i<N ; i++)
    {
        IndSets.insert({i, {i}});
        for(u64 j=0 ; j<N ; j++)
        {
            if(i==j) continue;
            if( isNotConnectedToSet(j, IndSets[i]) )
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
    for(u64 i=0 ; i<N ; i++)
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




// Génère un graphe qui représente une molecule d'eau (à des fins de tests majoritairement)
Graph H2O() {
    Graph graph(3);
    graph.connect(0, 1);
    graph.connect(0, 2);

    return graph;
}

// Génère un graphe qui représente une molecule de méthane (à des fins de tests majoritairement)
Graph Methane() {
    Graph graph(5);
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(0, 4);

    return graph;
}

// Génère un graphe qui représente une molecule en forme d'hexagone (à des fins de tests majoritairement)
Graph Hexagone() {
    Graph graph(6);

    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 4);
    graph.connect(4, 5);
    graph.connect(5, 0);
    
    return graph;
}


} // end namespace GM