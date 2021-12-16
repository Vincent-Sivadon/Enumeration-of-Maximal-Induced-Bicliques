#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <utility>
# define INF 0x3f3f3f3f

#include "visualisation.hpp"
#include "graph.hpp"

// connect 2 vertices i and j
void Graph::connect(int i, int j) {
    adj[i].push_back(j);
    adj[j].push_back(i);
}

void Graph::print() {
    for (int v = 0; v < N; ++v)
    {
        std::cout << "\n Neighboors of vertex "
             << v << "\n ";
        for (auto x : adj[v])
           std::cout << "-> " << x;
        printf("\n");
    }
}

// Check if an edge can be placed between 2 vertices s and d
bool Graph::areConnected(int i, int j) {
    for (auto& vertex : adj[i])
        if (vertex == j) return true;
    return false;
}


void Graph::draw() {
    drawGraph(*this);
}

Graph genRandGraph(int N) {
    Graph graph(N);

    for(int i=0 ; i<N ; i++)
        for(int j=0 ; j<N ; j++) {
            double r = (double) rand() / (double) RAND_MAX;
            if (r < 0.5) graph.connect(i, j);
        }
    
    return graph;
}

bool Graph::isProper(std::set<int> set) {
    for (int i=0 ; i<N ; i++) 
        if(set.find(i) == set.end()) return true;
    return false;
}

int minDist(std::vector<int>& dist, std::vector<bool>& visited) {
    // On initialisa la distance minimal à l'infini et l'index du noeud pour lequel la distance est minimal
    int min = INF, min_index=0;

    for(int v=0 ; v<dist.size() ; v++)
        if (!visited[v] && dist[v]<=min)
            min = dist[v], min_index = v;

    return min_index;
}

std::vector<int> Graph::shortestPaths(int src) {    
    /* On crée un tableau dynamique pour stocker les distances et on et 
    initialise toutes les distances à l'infini.
    Et on crée un ensemble pour dire si les sommets ont été visités */
    std::vector<int> dist(N, INF);
    std::vector<bool> visited(N, false);

    // On intialise ça distance à 0
    dist[src] = 0;

    // On fera au maximum N iterations
    for(int j=0 ; j<N ; j++)
    {
        // On calcul l'index du noeud pour lequel la distance est minimal 
        // On le supprime donc de l'ensemble
        int u = minDist(dist, visited);
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

Graph Graph::genSubgraph(int i) {

    // Obtenir les distances au le sommet i
    std::vector<int> dist = shortestPaths(i);

    //
    std::vector<std::pair<int,int>> connections;
    std::set<int> vertices;

    //
    for (int x = 0 ; x < N - 1 ; x++)
        for (int y = x+1 ; y < N ; y++) {
            bool are_connected = areConnected(x, y);

            // Vérification des distances
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
                vertices.insert(x); vertices.insert(y);
                connections.push_back(std::make_pair(x, y));
            }
        }

    Graph subgraph(vertices.size());
    subgraph.connect(1,4);
    /*
    for (auto& pair : connections) {
        subgraph.connect(pair.first, pair.second);
    }
    */
   std::cout << "IS OK \n";
    std::cout << subgraph.areConnected(1, 4) << "\n";

    return subgraph;
}


bool Graph::isNotConnectedToSet(int v, std::set<int> set)
{
    for (auto u : set){
        if (areConnected(v, u)) return false;
    }
    return true;
}

std::set<std::set<int>> Graph::getMaxIndSets() {
    std::vector<std::set<int>> IndSets(N);
    std::set<std::set<int>> maxIndSets;

    // Maximal set size
    int maxSize = 0;

    // Get maximal independent sets from the starting node i
    for (int i=0 ; i<N ; i++) {
        IndSets[i].insert(i);
        for (int j=0 ; j<N ; j++) {
            if(i==j) continue;
            if ( isNotConnectedToSet(j, IndSets[i]) ) {
                IndSets[i].insert(j);
            }
        }
        if(IndSets[i].size() > maxSize ) maxSize = IndSets[i].size();
    }

    // keep only the real maximal sets
    for (int i=0 ; i<N ; i++)
        if (IndSets[i].size() == maxSize) maxIndSets.insert(IndSets[i]);


    return maxIndSets;
}



// Utility function
void insertProperSuffixes(std::set<int> const& maxIndSet, std::set<std::set<int>>& bicliques) {
    std::set<int> properSuffixes;
    for(auto& el : maxIndSet) {
        properSuffixes.insert(el);
        bicliques.insert(properSuffixes);
    }
}


std::set<std::set<int>> Graph::getBicliques() {

    // Store bicliques
    std::set<std::set<int>> bicliques;
    
    //
    for(int i=0 ; i<N ; i++) {
        // Construct the subgraph G_i
        Graph subgraph_i = this->genSubgraph(i);

        // Get all maximal independent sets of G_i
        std::set<std::set<int>> maxIndSets = subgraph_i.getMaxIndSets();

        for(auto& maxIndSet : maxIndSets) {
            if (subgraph_i.isProper(maxIndSet)) {
                // Search if maxIndSet is already in bicliques
                if (bicliques.find(maxIndSet) == bicliques.end())
                    insertProperSuffixes(maxIndSet, bicliques);
            }
        }

    }

    return bicliques;
}




// Generate a graph that represent a H2O molecule (for testing purposes)
Graph H2O() {
    Graph graph(3);
    graph.connect(0, 1);
    graph.connect(0, 2);

    return graph;
}

// Generate a graph that represent a methane molecule (for testing purposes)
Graph Methane() {
    Graph graph(5);
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(0, 4);

    return graph;
}

// Generate a graph that represent an hexagone
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