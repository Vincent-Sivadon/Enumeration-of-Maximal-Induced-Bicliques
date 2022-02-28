#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

typedef struct edgeMin // structure dont les champs stockent le sommet de degré minimal et ledit degré
{
    int degree;
    int vertex;
} edgeMin;

/**
 * @brief structure dont les champs permettent de stocker les sommets dans l'ordre de leurs suppression ainsi que leurs degrés respectifs
 * degTab  -> contient les degrés des sommets,
 * vertTab -> contient les sommets.
 */
typedef struct degenElem
{  
    std::vector<int> degTab;
    std::vector<int> vertTab;
} degenElem;

/************ Fonction permettant de connaitre Le degre de chaque sommet*****/
std::vector<int> Find_degrees(std::vector<std::vector<int>> &graph, int Nb_vertices)
{
    std::vector<int> edgesDegree(graph.size());

    for (int i = 0; i < Nb_vertices; i++)
        edgesDegree[i] = graph[i].size();

    return edgesDegree;
}

/********* Fonction utilitaire permettant d'afficher le tableau des degrés *******************/
void PrintVerticesDeg(std::vector<int> &Vertices)
{
    for (int i = 0; i < Vertices.size(); i++)
    {
        std::cout << "Sommet " << i << ": " << Vertices[i] << "\n";
    }
}

/******** Fonction utilitaire permettant d'afficher le graphe ***********************************/

void printGraph(std::vector<std::vector<int>> &graph, int N)
{
    for (int i = 0; i < graph.size(); i++)
    {
        std::cout << "voisins de " << i << ": ";
        for (auto x : graph[i])
            std::cout << x << ", ";
        std::cout << std::endl;
    }
}

/**
 * Fonction permettant d'ajouter des arretes un graphe modeliser par une liste d'adjacence
 */
void addEdge(std::vector<std::vector<int>> &graph, int a, int b)
{
    graph[a].push_back(b);
    graph[b].push_back(a);
}

bool isGraphEmpty(std::vector<std::vector<int>> &graph, int N) {
    auto degrees = Find_degrees(graph, N);
    return std::all_of(degrees.cbegin(), degrees.cend(), [](auto const &e) {
        return e == 0;
    });
}

/**
 * fonction permettant de trouver les sommets de degrés minimum ainsi que le degré minimal d'un graphe passé en argument
 * 
 * 
 * 
 */
edgeMin FindVertexDegMin(std::vector<std::vector<int>> &graph, int N)
{
    assert(!isGraphEmpty(graph, N));
    edgeMin s;
    std::vector<int> EdgeDeg = Find_degrees(graph, N); // Trouver les degrés de chaque sommet du graphe passé en argument et les stocker dans un tableau

    int vertexWithDegMin = 0;
    for(int i = 0; i < N; i++) {
        if(EdgeDeg[i] <= 0) 
            continue;
        vertexWithDegMin = i;
        break;
    }

    int minEdgeDeg = EdgeDeg[vertexWithDegMin]; // On commence également par initialisé le degré minimial par le degré du premier sommet

    for (int i = 0; i < N; i++) // Parcourir le tableau des degrés à la recherche du sommet de degré minimal
    {
        if ((EdgeDeg[i] < minEdgeDeg) && !(graph[i].empty()))
        {
            minEdgeDeg = EdgeDeg[i]; // Mettre à jour le degré minimal
            vertexWithDegMin = i;    // Mettre à jour le sommet de degré minimal
        }
    }
    s.degree = minEdgeDeg;
    s.vertex = vertexWithDegMin;

    return s;
}

/* Fonction utilitaire pour afficher le degrée d'un minimal et le sommet du graphe ayant ce degré*****************/
void printMinVertex(edgeMin s)
{
    std::cout << " Vertex with minimum degree :" << s.vertex << "\n";
    std::cout << " Minimal degree : " << s.degree << "\n";
}

/*void delNode(std::vector<int>graph[], int N, int node) {
    for(int i = 0; i< N; i++){
        auto finded = std::find(graph[i].begin(), graph[i].end(), node);
        if(finded != graph[i].end())
            graph[i].erase(graph[i].begin(), finded);
    }
}*/

/* Fonction pour supprimer les sommets d'un graphe ****/

void delVertices(std::vector<std::vector<int>> &graph, int N, int node, std::vector<bool> &StateNodes)
{
    /* pour des raisons de performance et de portabilité nous optons pour cet approche
                                                en effet dès qu'un sommet est supprimé nous rentrons dans le tableau state pour
                                                mettre à jour la valeur se trouvant à l'index correspondant */

    std::vector<int> traceNode{}; // Pour suivre l'odre de suppression des sommets.
    StateNodes[node] = true;
    traceNode.push_back(node); // L'objectif est de retracer l'odre de suppression des sommets
}

/* Fonction pour supprimer une arête dans un graphe ****/

void delEdge(std::vector<std::vector<int>> &graph, int a, int b)
{
    // parcourir la liste des voisins du premier sommet à la recherche du second puis l'enlever dès qu'on le trouve
    for (int i = 0; i < graph[a].size(); i++)

    {
        if (graph[a][i] == b)
        {
            graph[a].erase(graph[a].begin() + i);
            break;
        }
    }

    /* if (graph[a].empty())
    {
        graph.erase(graph.begin() + a);
    }
*/
    // parcourir la liste des voisins du deuxième sommet à la recherche du premier puis l'enlever dès qu'on le trouve
    for (int i = 0; i < graph[b].size(); i++)
    {
        if (graph[b][i] == a)
        {
            graph[b].erase(graph[b].begin() + i);
            break;
        }
    }
    /*
    if (graph[b].empty())
    {
        graph.erase(graph.begin() + b);
    } */
}



/****************************Algo de degenerescence **********************/
// template <typename T>
// void degenOrder(const Graph<T> &graph, int N)
degenElem degenOrder(std::vector<std::vector<int>> &graph, int N)
{
    degenElem dge;
    std::vector<int> rmdeg;
    std::vector<int> rmVertices;
    int tmp = 0;
    while (!isGraphEmpty(graph, N) && tmp++ < 10)
    {
        printGraph(graph, N);
        edgeMin s = FindVertexDegMin(graph, N);
        std::cout << "degre : " << s.degree;
        rmdeg.push_back(s.degree);
        std::cout << "  ; node : " << s.vertex;
        rmVertices.push_back(s.vertex);
        std::cout << "\n";

        for (auto u : graph[s.vertex])
        {
            delEdge(graph, s.vertex, u);
        }
    }
    dge.degTab  = rmdeg;
    dge.vertTab = rmVertices;
    return dge ;
}

int main()
{
    int N = 5;
    // Graph
    std::vector<std::vector<int>> graph(5);
    /*for (unsigned i=0; i<5; i++)
        graph.emplace_back();*/

    // Ajout des arêtes
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    //

    // printGraph(graph, N);

    /*
        std::vector<int> VertDeg = Find_degrees(graph,N);

        PrintVercticesDeg(VertDeg);

        edgeMin s = FindVertexDegMin(graph,N);
        printf("\n");
        printMinVertex(s);

        printf("\n"); */
    // delEdge(graph, 1, 2);
    // degenOrder(graph, N);
    /*
    edgeMin s = FindVertexDegMin(graph, N);
    printf("\n");
    std::vector<int> VertDeg = Find_degrees(graph, N);

    PrintVerticesDeg(VertDeg);
    printMinVertex(s);

    delEdge(graph, 0, 1);
    delEdge(graph, 0, 4);

    edgeMin u = FindVertexDegMin(graph, N);
    printf("\n");
    VertDeg = Find_degrees(graph, N);
    PrintVerticesDeg(VertDeg);
    printMinVertex(u);*/

    degenElem d = degenOrder(graph, N);
    // delEdge(graph, 0, 4);
    // std::cout << graph[0].empty() << "\n";
    printGraph(graph, N);
    //   printGraph(graph,N);
    for (auto i :d.vertTab )
    {
        std::cout << i << " ";
    }
    return 0;
}