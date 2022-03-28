/*
    - Contient l'implémentation de la structure Graph.
*/

#pragma once

/* =============================== SETS =============================== */

// Retourn un booléen indiquant si un set est propre par rapport au graphe
template <typename T>
bool Graph<T>::isProper(std::set<u64> set)
{
    for (auto i = set.begin(); i != set.end(); i++)
        for (auto j = set.begin(); j != set.end(); j++)
            if (i != j)
                if (areConnected(*i, *j))
                    return true;
    return false;
}

// Indique si vertex est connecté au set dans le graphe
template <typename T>
bool Graph<T>::isConnectedToSet(u64 v, std::set<u64> set)
{
    for (const auto &u : set)
    {
        if (areConnected(v, u))
            return true;
    }
    return false;
}

// Enumère tout les set indépendants
template <typename T>
void Graph<T>::getIndSets(std::set<std::set<u64>> &IndSets, std::set<u64> &tmpSet, u64 i)
{
    for (u64 j = i; j < N; j++)
    {
        // On ajoute j au tmpSet si il n'est connecté à aucun k de tmpSet
        if (isConnectedToSet(j, tmpSet))
            continue;

        // Si on a passé le test, on insert j
        tmpSet.insert(j);

        // on refait la procédure à partir de j+1
        getIndSets(IndSets, tmpSet, j + 1);

        // Puisqu'on a construit le set indépendants qui partait de j, on le supprime du tmpSet
        tmpSet.erase(j);
    }
    IndSets.insert(tmpSet);
}

// Enumère tout les sets indépendants maximaux du graphe
template <typename T>
std::set<std::set<u64>> Graph<T>::getMaxIndSets()
{
    //
    std::set<std::set<u64>> IndSets;
    std::set<u64> tmpSet;
    std::set<std::set<u64>> maxIndSets;

    // Get all independent sets
    getIndSets(IndSets, tmpSet, 0);

    // Taille du set maximal pour pouvoir isoler que les max ind sets
    u64 maxSize = 0;
    for (const auto &set : IndSets)
        if (set.size() > maxSize)
            maxSize = set.size();

    // On garde uniquement les sets de taille maximale
    for (const auto &set : IndSets)
        if (set.size() == maxSize)
            maxIndSets.insert(set);

    return maxIndSets;
}

/* ============================= UTILITAIRE ============================= */

// Donne la longueur du plus court chemin depuis src pour chaque sommet
template <typename T>
std::vector<u64> Graph<T>::shortestPaths(u64 src)
{
    /* On crée un tableau dynamique pour stocker les distances et on et
    initialise toutes les distances à l'infini.
    Et on crée un ensemble pour dire si les sommets ont été visités */
    std::vector<u64> dist(N, INF);
    std::vector<bool> visited(N, false);

    // On intialise ça distance à 0
    dist[src] = 0;

    // On fera au maximum N iterations
    for (u64 j = 0; j < N; j++)
    {
        // On calcul l'index du noeud pour lequel la distance est minimal
        // On le supprime donc de l'ensemble
        u64 u = minDist(dist, visited);
        visited[u] = true;

        // On vérifie que u ne dépasse pas la distance souhaitée
        if (dist[u] >= 2)
            break;

        // On boucle sur tous les voisins contenues dans adj
        for (u64 v = 0; v < N; v++)
        {
            // si adj[u][v] = 0 alors ils ne sont pas voisins
            if (!areConnected(u, v))
                continue;

            // On met à jour la plus courte distance si besoin
            if (dist[v] > dist[u] + 1 && !visited[v])
                dist[v] = dist[u] + 1;
        }
    }

    return dist;
}

/* ======================== PROCEDURE DE L'ARTICLE ======================== */

// Génère les sous-graphes d'après le papier (sigma contiendra l'ordre des sommets)
template <typename T>
Graph<T> Graph<T>::genSubgraph(u64 i)
{
    // Obtenir les distances au sommet i
    std::vector<u64> dist = shortestPaths(i);

    //
    Graph<T> subgraph(N - i);

    // Run through all pairs of nodes in the parent graph
    for (u64 x = i; x < N; x++)
        for (u64 y = x + 1; y < N; y++)
        {
            bool are_connected = areConnected(x, y);

            // Conditions  de construction des arretes
            bool x_dist1 = (dist[x] == 1 ? true : false);
            bool y_dist1 = (dist[y] == 1 ? true : false);
            bool x_dist2 = (dist[x] == 2 ? true : false);
            bool y_dist2 = (dist[y] == 2 ? true : false);

            // Conditions  de construction des arretes
            bool cond1 = x_dist1 && y_dist1 && are_connected;
            bool cond2 = x_dist2 && y_dist2 && are_connected;
            bool cond3 = x_dist1 && y_dist2 && !are_connected;
            bool cond4 = x_dist2 && y_dist1 && !are_connected;

            // Ajouter une arrete si l'une des conditions est vérifiée
            if (cond1 || cond2 || cond3 || cond4)
                // Add node x and y with new indices to the pairs of the subgraph
                subgraph.connect(x - i, y - i);
        }

    return subgraph;
}

// Enumère tout les bicliques maximales du graphe
template <typename T>
std::set<std::set<u64>> Graph<T>::getBicliques()
{
    int rank, nproc;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (N % nproc != 1)
    {
        std::cout << "Number of nodes % number of processus must be 1\n";
        exit(1);
    }

    /* Rank 0 will gather bicliques, others will work */
    // if (rank == 0)
    Tree suffixTree;

    if (rank != 0)
    {

        // Dispatch
        int sectionSize = N / (nproc - 1);
        int ibeg = (rank - 1) * sectionSize;
        int iend = rank * sectionSize;

        //
        for (u64 i = ibeg; i < iend; i++)
        {
            // Construct the subgraph G_i
            Graph subgraph_i = genSubgraph(i);

            // Get all maximal independent sets of G_i
            std::set<std::set<u64>> maxIndSets = subgraph_i.getMaxIndSets();

            // Rename the nodes
            std::set<std::set<u64>> globalMaxIndSets; // sets with parent graph indices
            std::set<u64> tmp;
            for (const auto &maxIndSet : maxIndSets)
            {
                // Add the sets with parent graph indices
                tmp.clear();
                for (const auto &el : maxIndSet)
                    tmp.insert(el + i);
                globalMaxIndSets.insert(tmp);
            }

            // Add maxIndSet
            for (const auto &maxIndSet : globalMaxIndSets)
                if (isProper(maxIndSet))
                    suffixTree.insert(maxIndSet);
        }

        // On isole les branches maximale de l'arbre de suffix
        std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

        // MPI

        // Get size
        int nbEl = 0, nbBicliques = bicliques.size();
        for (const auto &biclique : bicliques)
            for (const auto &el : biclique)
                nbEl++;

        // Allocate memory for array to be sent
        int *data = (int *)malloc(nbEl * sizeof(int));
        int *offsets = (int *)malloc(nbBicliques * sizeof(int));

        // Fill arrays
        int i = 0, j = 0;
        for (const auto &biclique : bicliques)
        {
            offsets[j] = i;
            j++;
            for (const auto &el : biclique)
            {
                data[i] = el;
                i++;
            }
        }

        MPI_Send(data, nbEl, MPI_INT, 0, 1000, MPI_COMM_WORLD);
        MPI_Send(offsets, nbBicliques, MPI_INT, 0, 2000, MPI_COMM_WORLD);
    }
    else
    {
        int nbEl, nbBicliques;
        MPI_Status status_data, status_offsets;
        int *data, *offsets;

        for (int i = 0; i < nproc - 1; i++)
        {
            // Data message
            MPI_Probe(MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &status_data);
            MPI_Get_count(&status_data, MPI_INT, &nbEl);
            data = (int *)realloc(data, nbEl * sizeof(int));

            // Offsets message
            MPI_Probe(MPI_ANY_SOURCE, 200, MPI_COMM_WORLD, &status_offsets);
            MPI_Get_count(&status_offsets, MPI_INT, &nbBicliques);
            offsets = (int *)realloc(offsets, nbBicliques * sizeof(int));

            // Receives message
            MPI_Recv(data, nbEl, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(offsets, nbBicliques, MPI_INT, 0, 2000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Display test
            // ------------
            for (int j = 0; j < nbEl; j++)
                std::cout << data[j] << " ";
            std::cout << std::endl;
        }
    }

    std::set<std::set<u64>> bicliques = suffixTree.getMaxBranches();

    MPI_Finalize();

    return bicliques;
}

/* =========================== GENERATION DE GRAPHE =========================== */

// Génère un graphe pour lequel chaque sommet a 50% de chance d'être connecté à un autre sommet
template <typename T>
Graph<T> genRandGraph(u64 N)
{
    // Déclaration d'un nouveau graphe
    Graph<T> graph(N);

    // On ajoute une arrête entre i et j avec une probabilité de 50%
    for (u64 i = 0; i < N; i++)
        for (u64 j = 0; j < N; j++)
        {
            // Nombre aléatoire entre 0 et 1
            double r = (double)rand() / (double)RAND_MAX;

            // Connecte i et j si r<0.5
            if (r < 0.5)
                graph.connect(i, j);
        }

    return graph;
}

/* ============================= GRAPHES SIMPLES ============================= */

// Génère un graphe représentant une molécule de H2O
template <typename T>
Graph<T> H2O()
{
    Graph<T> graph(3);
    graph.connect(0, 1);
    graph.connect(0, 2);

    return graph;
}

// Génère un graphe représentant une molécule de méthane
template <typename T>
Graph<T> Methane()
{
    Graph<T> graph(5);
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(0, 4);

    return graph;
}

// Génère un graphe représentant un hexagone
template <typename T>
Graph<T> Hexagone()
{
    Graph<T> graph(6);

    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 4);
    graph.connect(4, 5);
    graph.connect(5, 0);

    return graph;
}

/* =========================== FONCTION UTILITAIRE =========================== */

// Recherche du sommet avec la distance minimale
u64 minDist(std::vector<u64> &dist, std::vector<bool> &visited)
{
    // On initialisa la distance minimal à l'infini et l'index du noeud pour lequel la distance est minimal
    u64 min = INF, min_index = 0;

    for (u64 v = 0; v < dist.size(); v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSets(std::set<std::set<u64>> sets)
{
    for (auto &set : sets)
    {
        for (auto &i : set)
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}
